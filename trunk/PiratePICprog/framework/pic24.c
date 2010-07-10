
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
	iface->SetBitOrder(opts, BIT_MSB);
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
	iface->SetBitOrder(opts, BIT_LSB);
	//puts("(OK)");

	//first 9bit SIX command, setup the PIC ICSP
	iface->SendBits(opts, 5, 0x00);//five extra clocks on first SIX command after ICSP mode
	iface->PIC424Write(opts, 0x040200, 0, 0);
	iface->PIC424Write(opts, 0x040200, 0, 3);//SIX,0x040200,5, NOP
	iface->PIC424Write(opts, 0x040200, 0, 1);//SIX,0x040200,5, goto 0x200
}

uint32_t PIC24_ExitICSP(struct picprog_t *p) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	//exit programming mode
	iface->MCLRLow(opts);
	iface->MCLRHigh(opts);
}

uint32_t PIC24_ReadID(struct picprog_t *p) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint32_t id;

	PIC24_Read(opts, 0x00FF0000, (void*)&id, 2); //give it the ID addres

	return id;
}

uint32_t PIC24_Read(struct picprog_t *p, uint32_t addr, void* Data, uint32_t length) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint32_t ctr, nopctr=0;
	
	iface->PIC424Write(opts, 0x200000 | ((addr & 0xffff0000) >> 12), 0, 0);//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
	iface->PIC424Write(opts, 0x880190, 0, 0);//SIX,0x880190,5, N/AMOV W0, TBLPAG
	iface->PIC424Write(opts, 0x200006 | ((addr & 0x000ffff) << 4), 0, 2);//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6

	iface->PIC424Write(opts, 0x207847, 0, 1);//SIX,0x200007,5, N/A  //MOV #VISI,W7
	//PIC24NOP();//SIX,0x000000,5, N/A
	
	for(ctr = 0; ctr < length; ctr++){
		iface->PIC424Write(opts, 0xBA0BB6, 0, 2); //SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++]
		((uint16_t*)Data)[ctr] = iface->PIC424Read(opts); //REGOUT,0x000000,5, read VISI register (PIC includes 2 NOPS after every read, may need to be updated later)
		//printf("Read: %X \n",Data[ctr]); //REGOUT,0x000000,5, read VISI register
	
		//every so often we need to reset the address pointer or it will fall off the end
		//also do it the last time
		nopctr++;
		if((nopctr > 10) || ((ctr + 1) == length)){
			nopctr = 0; //only do occasionally
			PIC24NOP();//SIX,0x000000,5, N/A
			iface->PIC424Write(opts, 0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)
		}
	}
	return 0;
}

//18F setup write location and write length bytes of data to PIC
uint32_t PIC24_Write(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint16_t DataByte;//, buffer[2]={0x00,0x00};
	uint32_t ctr;
	uint8_t	buffer[4] = {0};
	uint16_t VISI;

	//set NVMCON
	iface->PIC424Write(opts, 0x24001A, 0, 0); //MOV XXXX,W10 0x4001 (differs by PIC)
	iface->PIC424Write(opts, 0x883B0A, 0, 0); //MOV W10,NVMCON

	//setup the table pointer
	iface->PIC424Write(opts, 0x200000, 0, 0); //MOV XXXX,W0 (0x0000)
	iface->PIC424Write(opts, 0x880190, 0, 1); //MOV W0,TABLPAG
	iface->PIC424Write(opts, 0x200007, 0, 0); //MOV XXXX,W7 (0x0000)
	
	for(ctr = 0; ctr < 16; ctr++)
	{	
		iface->PIC424Write(opts, 0x200000, 0, 0); //MOV XXXX,W0 (0x0000)
		iface->PIC424Write(opts, 0x200001, 0, 0); //MOV XXXX,W1 (0x0000)
		iface->PIC424Write(opts, 0x200002, 0, 0); //MOV XXXX,W2(0x0000)
		iface->PIC424Write(opts, 0x200003, 0, 0); //MOV XXXX,W3 (0x0000)
		iface->PIC424Write(opts, 0x200004, 0, 0); //MOV XXXX,W4 (0x0000)
		iface->PIC424Write(opts, 0x200005, 0, 0); //MOV XXXX,W5 (0x0000)	

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
		
	//repeat until write done, should reset counter every now and then too... 11000000 01001111
	while(1) {
		PIC24NOP();
		iface->PIC424Write(opts, 0x803B02, 0, 2);//MOV NVMCON,W2
		iface->PIC424Write(opts, 0x883C22, 0, 2);//MOV W2,VISI	

		VISI = iface->PIC424Read(opts);//REGOUT,0x000000,5, read VISI register (PIC includes 2 NOPS after every read, may need to be updated later)
		//printf("Read: %X \n",VISI); //REGOUT,0x000000,5, read VISI register
		PIC24NOP();//SIX,0x000000,5, N/A
		iface->PIC424Write(opts, 0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)

		if(!(VISI & 0x8000)) break; //bit15 will clear when erase is done
	}
	return 0;
}

uint32_t PIC24_Erase(struct picprog_t *p) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint16_t VISI;
	
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
	while(1){
		PIC24NOP();
		iface->PIC424Write(opts, 0x803B02, 0, 2);//MOV NVMCON,W2
		iface->PIC424Write(opts, 0x883C22, 0, 2);//MOV W2,VISI	

		VISI = iface->PIC424Read(opts);//REGOUT,0x000000,5, read VISI register (PIC includes 2 NOPS after every read, may need to be updated later)
		//printf("Read: %X \n",VISI); //REGOUT,0x000000,5, read VISI register
		PIC24NOP();//SIX,0x000000,5, N/A
		iface->PIC424Write(opts, 0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)

		if(!(VISI & 0x8000)) break; //bit15 will clear when erase is done
	}
	return 0;
}

