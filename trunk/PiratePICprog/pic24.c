#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "pic.h"
#include "iface.h"
#include "pic24.h"


#define PIC24NOP() 	iface->PIC424Write(opts, 0x000000,0,0)

uint32_t PIC24_EnterICSP(struct picprog_t *p, enum icsp_t type) {
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint8_t	buffer[4];

	//all programming operations are LSB first, but the ICSP entry key is MSB first.
	// Reconfigure the mode for LSB order
	//printf("Set mode for MCLR (MSB)...");
	//iface->SetBitOrder(opts, BIT_MSB);
	//puts("(OK)");

	iface->ClockLow(opts);
	iface->DataLow(opts);
	iface->MCLRLow(opts);
	iface->MCLRHigh(opts);
	iface->MCLRLow(opts);

   //send ICSP key 0x4D434850
	buffer[0] = f->icsp_key >> 24;
	buffer[1] = f->icsp_key >> 16;
	buffer[2] = f->icsp_key >> 8;
	buffer[3] = f->icsp_key;

	iface->SendBytes(opts, 4, buffer);
	iface->DataLow(opts);
	iface->MCLRHigh(opts);

	//all programming operations are LSB first, but the ICSP entry key is MSB first.
	// Reconfigure the mode for LSB order
	//printf("Set mode for PIC programming (LSB)...");
	//iface->SetBitOrder(opts, BIT_LSB);
	//puts("(OK)");

	//setup the Bus Pirate for 424 writes


	//first 9bit SIX command, setup the PIC ICSP
	iface->SendBits(opts, 5, 0x00);//five extra clocks on first SIX command after ICSP mode
	iface->PIC424Write(opts, 0x040200, 0, 0);
	iface->PIC424Write(opts, 0x040200, 0, 3);//SIX,0x040200,5, NOP
	iface->PIC424Write(opts, 0x040200, 0, 1);//SIX,0x040200,5, goto 0x200
	iface->flush(opts);
	return 0;
}

uint32_t PIC24_ExitICSP(struct picprog_t *p, enum icsp_t type) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	//exit programming mode
	iface->MCLRLow(opts);
	iface->MCLRHigh(opts);
	return 0;
}

uint32_t PIC24_ReadID(struct picprog_t *p, uint16_t *id, uint16_t *rev) {
    struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
//	struct iface_t *iface = p->iface;
//	void *opts = p->iface_data;
	uint32_t PICid;

    PIC24_EnterICSP(p, f->icsp_type);

	PIC24_Read(p, 0x00FF0000, (void*)&PICid, 4); //give it the ID addres

    PIC24_ExitICSP(p, f->icsp_type);

    //determine device type
	*rev=(uint16_t)(PICid>>16); //find PIC ID (lower 16 bits)
	*id=(uint16_t)(PICid&(~0xFFFF0000)); //isolate revision (upper 16 bits)

	return PICid;
}

uint32_t PIC24_Read(struct picprog_t *p, uint32_t addr, void* Data, uint32_t length) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint32_t ctr, nopctr=0;

	iface->PIC424Write(opts, 0x200000 | ((addr & 0xffff0000) >> 12), 0, 0);//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
	iface->PIC424Write(opts, 0x880190, 0, 0);//SIX,0x880190,5, N/AMOV W0, TBLPAG
	iface->PIC424Write(opts, 0x200006 | ((addr & 0x000ffff) << 4), 0, 2);//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6
	iface->PIC424Write(opts, 0x207847, 0, 1);//SIX,0x200007,5, N/A  //MOV #VISI,W7 //PIC24NOP();//SIX,0x000000,5, N/A
    iface->flush(opts);
	//for(ctr = 0; ctr < length; ctr++){
		//iface->PIC424Write(opts, 0xBA0BB6, 0, 2); //SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++]
        //iface->flush(opts);
        iface->PIC424Read(opts, 0xBA0BB6, Data, length);
		//((uint16_t*)Data)[ctr] = iface->PIC424Read(opts);//, 0xBA0BB6, 0, 2); //REGOUT,0x000000,5, read VISI register (PIC includes 2 NOPS after every read, may need to be updated later)
		//printf("Read: %X \n",Data[ctr]); //REGOUT,0x000000,5, read VISI register

		//every so often we need to reset the address pointer or it will fall off the end
		//also do it the last time
		//nopctr++;
		//if((nopctr > 10) || ((ctr + 1) == length)){
		//	nopctr = 0; //only do occasionally
			PIC24NOP();//SIX,0x000000,5, N/A
			iface->PIC424Write(opts, 0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)
            iface->flush(opts);
		//}
	//}
	//iface->flush(opts);
	return 0;
}

//18F setup write location and write length bytes of data to PIC
uint32_t PIC24_Write(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
//	uint16_t DataByte;//, buffer[2]={0x00,0x00};
	uint32_t ctr, tem, tem1;
//	uint8_t	buffer[4] = {0};
	uint16_t VISI;


	//set NVMCON
	iface->PIC424Write(opts, 0x24001A, 0, 0); //MOV XXXX,W10 0x4001 (differs by PIC)
	iface->PIC424Write(opts, 0x883B0A, 0, 0); //MOV W10,NVMCON
    tblptr=tblptr/2;
    //setup the table pointer
	iface->PIC424Write(opts, 0x200000 | ((tblptr & 0xffff0000) >> 12), 0, 0);//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
	iface->PIC424Write(opts, 0x880190, 0, 1);//SIX,0x880190,5, N/AMOV W0, TBLPAG
	iface->PIC424Write(opts, 0x200007 | ((tblptr & 0x000ffff) << 4), 0, 2);//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6

	for(ctr = 0; ctr < 16; ctr++) //really this is fixed at 16
	{
		//iface->PIC424Write(opts, 0x200000 | ((((uint16_t *)Data)[ctr])<< 4), 0, 0); //MOV XXXX,W0 (0x0000) X10
		iface->PIC424Write(opts, 0x200000 | ((((uint8_t *)Data)[(ctr*16)+1])<< 12)|((((uint8_t *)Data)[(ctr*16)])<< 4), 0, 0);
	//	iface->PIC424Write(opts, 0x200001 | ((((uint16_t *)Data)[ctr+1])<< 4), 0, 0); //MOV XXXX,W1 (0x0000) 2XX/3XX
        iface->PIC424Write(opts, 0x200001 | ((((uint8_t *)Data)[(ctr*16)+6])<< 12)|((((uint8_t *)Data)[(ctr*16)+2])<< 4), 0, 0);
	//	iface->PIC424Write(opts, 0x200002 | ((((uint16_t *)Data)[ctr+2])<< 4), 0, 0); //MOV XXXX,W2(0x0000) X54
        iface->PIC424Write(opts, 0x200002 | ((((uint8_t *)Data)[(ctr*16)+5])<< 12)|((((uint8_t *)Data)[(ctr*16)+4])<< 4), 0, 0);
	//	iface->PIC424Write(opts, 0x200003 | ((((uint16_t *)Data)[ctr+3])<< 4), 0, 0); //MOV XXXX,W3 (0x0000)
	    iface->PIC424Write(opts, 0x200003 | ((((uint8_t *)Data)[(ctr*16)+9])<< 12)|((((uint8_t *)Data)[(ctr*16)+8])<< 4), 0, 0);
	//	iface->PIC424Write(opts, 0x200004 | ((((uint16_t *)Data)[ctr+4])<< 4), 0, 0); //MOV XXXX,W4 (0x0000)
	    iface->PIC424Write(opts, 0x200004 | ((((uint8_t *)Data)[(ctr*16)+14])<< 12)|((((uint8_t *)Data)[(ctr*16)+10])<< 4), 0, 0);
	//	iface->PIC424Write(opts, 0x200005 | ((((uint16_t *)Data)[ctr+5])<< 4), 0, 0); //MOV XXXX,W5 (0x0000)
	    iface->PIC424Write(opts, 0x200005 | ((((uint8_t *)Data)[(ctr*16)+13])<< 12)|((((uint8_t *)Data)[(ctr*16)+12])<< 4), 0, 0);

		iface->PIC424Write(opts, 0xEB0300, 0, 1);//CLR W6
		iface->PIC424Write(opts, 0xBB0BB6, 0, 2);	//TBLWTL [W6++], [W7]
		iface->PIC424Write(opts, 0xBBDBB6, 0, 2);	//TBLWTH.B [W6++], [W7++]
		iface->PIC424Write(opts, 0xBBEBB6, 0, 2);	//TBLWTH.B [W6++], [++W7]
		iface->PIC424Write(opts, 0xBB1BB6, 0, 2); //TBLWTL [W6++], [W7++]
		iface->PIC424Write(opts, 0xBB0BB6, 0, 2);	//TBLWTL [W6++], [W7]
		iface->PIC424Write(opts, 0xBBDBB6, 0, 2);	//TBLWTH.B [W6++], [W7++]
		iface->PIC424Write(opts, 0xBBEBB6, 0, 2);	//TBLWTH.B [W6++], [++W7]
		iface->PIC424Write(opts, 0xBB1BB6, 0, 2);	//TBLWTL [W6++], [W7++]
	}

	//start the write cycle
	iface->PIC424Write(opts, 0xA8E761, 0, 2); //BSET NVMCON, #WR
    iface->flush(opts);

	//repeat until write done, should reset counter every now and then too... 11000000 01001111
	//while(1) {
		//PIC24NOP();
		//iface->PIC424Write(opts, 0x803B02, 0, 2);//MOV NVMCON,W2
		//iface->PIC424Write(opts, 0x883C22, 0, 2);//MOV W2,VISI
        //iface->flush(opts);

		//VISI = iface->PIC424Read(opts,0xBA0BB6, Data, 1);//REGOUT,0x000000,5, read VISI register (PIC includes 2 NOPS after every read, may need to be updated later)
		//printf("Read: %X \n",VISI); //REGOUT,0x000000,5, read VISI register
		PIC24NOP();//SIX,0x000000,5, N/A
		iface->PIC424Write(opts, 0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)
        iface->flush(opts);
        usleep(3000);
		//if(!(VISI & 0x8000)) break; //bit15 will clear when erase is done
	//}
	return 0;
}

uint32_t PIC24_Erase(struct picprog_t *p) {
    struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint16_t VISI;

	PIC24_EnterICSP(p, f->icsp_type);

	//set NVMCON
	iface->PIC424Write(opts, 0x2404FA, 0, 0); //MOV XXXX,W10 0x404F (differs by PIC)
	iface->PIC424Write(opts, 0x883B0A, 0, 0); //MOV W10,NVMCON

	// Step 3: Set TBLPAG
	iface->PIC424Write(opts, 0x200000, 0, 0); //MOV XXXX,W0 (0x0000)
	iface->PIC424Write(opts, 0x880190, 0, 1); //MOV W0,TABLPAG
	iface->PIC424Write(opts, 0xBB0800, 0, 2); //TBLWTL W0,[W0] (dummy write)

	iface->PIC424Write(opts, 0xA8E761, 0, 2); //BSET NVMCON,#WR
	//sleep(1);

	//repeat until erase done, should reset counter every now and then too... 11000000 01001111
	//while(1){
		//PIC24NOP();
		//iface->PIC424Write(opts, 0x803B02, 0, 2);//MOV NVMCON,W2
		//iface->PIC424Write(opts, 0x883C22, 0, 2);//MOV W2,VISI
        //iface->flush(opts);

		//VISI = iface->PIC424Read(opts);//REGOUT,0x000000,5, read VISI register (PIC includes 2 NOPS after every read, may need to be updated later)
		//printf("Read: %X \n",VISI); //REGOUT,0x000000,5, read VISI register
		PIC24NOP();//SIX,0x000000,5, N/A
		iface->PIC424Write(opts, 0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)
        iface->flush(opts);

		//if(!(VISI & 0x8000)) break; //bit15 will clear when erase is done
        usleep(1000 * f->erase_delay);
	//}

    PIC24_ExitICSP(p, f->icsp_type);

	return 0;
}

