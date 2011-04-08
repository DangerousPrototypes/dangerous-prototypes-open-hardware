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
	char	buffer[4];

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
	uint8_t buf[6];

    PIC24_EnterICSP(p, f->icsp_type);

	PIC24_Read(p, 0x00FF0000, &buf, 1); //give it the ID addres

    PIC24_ExitICSP(p, f->icsp_type);

    PICid=( buf[0] | (buf[1]<<8) | (buf[2]<<16) | (buf[3]<<24) );
    //determine device type
	*rev=(uint16_t)(PICid>>16); //find PIC ID (lower 16 bits)
	*id=(uint16_t)(PICid&(~0xFFFF0000)); //isolate revision (upper 16 bits)

	return ( buf[0] | (buf[1]<<8) );
}

uint32_t PIC24_Read(struct picprog_t *p, uint32_t addr, void* Data, uint32_t length) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	iface->PIC424Write(opts, 0x200000 | ((addr & 0xffff0000) >> 12), 0, 0);//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
	iface->PIC424Write(opts, 0x880190, 0, 0);//SIX,0x880190,5, N/AMOV W0, TBLPAG
	iface->PIC424Write(opts, 0x200006 | ((addr & 0x000ffff) << 4), 0, 2);//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6
	iface->PIC424Write(opts, 0x207847, 0, 1);//SIX,0x200007,5, N/A  //MOV #VISI,W7 //PIC24NOP();//SIX,0x000000,5, N/A
    iface->flush(opts);

    iface->PIC424Read(opts, 0xBA0BB6, Data, length);

    PIC24NOP();//SIX,0x000000,5, N/A
    iface->PIC424Write(opts, 0x040200, 0, 2);
    iface->flush(opts);

	return 0;
}

//18F setup write location and write length bytes of data to PIC
uint32_t PIC24_Write(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
//	uint16_t DataByte;//, buffer[2]={0x00,0x00};
	uint32_t ctr;//, tem, tem1;
//	uint8_t	buffer[4] = {0};
	//uint16_t VISI;


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
	//uint16_t VISI;

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

uint32_t PIC24_WriteFlash(struct picprog_t *p, uint8_t *fw_data)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *fam = PIC_GetFamily(pic->family);

	uint32_t u_addr;
	uint32_t page  = 0;
	uint32_t done  = 0;
	uint8_t used = 0, t;
	uint16_t i = 0;//, ctr;

    PIC24_EnterICSP(p, fam->icsp_type);

	for (page = 0; page < pic->flash / fam->page_size; page++)
	{
		u_addr = page * fam->page_size;
		//( PIC_NUM_WORDS_IN_ROW * 2 * PIC_NUM_ROWS_IN_PAGE );
		//u_addr = page * ( 2 * 32 );

		// check used page
		used = 0;
		t=0;
		for (i = 0; i < fam->page_size; i++) {
                t++;
                if(t==4){
                    t=0;
                    continue;
                }

                if (fw_data[u_addr+i] != PIC_EMPTY) {
                    used = 1;
                    break;
                }
		}

		// skip unused
		if (used == 0 ) {
			if (u_addr < pic->flash) {
				fprintf(stdout, "Skipping page %ld [ 0x%06lx ], not used\n", (unsigned long)page, (unsigned long)u_addr);
			}
			continue;
		}

		if (u_addr >= pic->flash) {
			fprintf(stderr, "Address out of flash\n");
			continue;
		}

		printf("Writing page %ld, %04lx... \n", (unsigned long)page, (unsigned long)u_addr);

//		if (p->debug) {
//			dumpHex(&fw_data[page * fam->page_size], fam->page_size);
//		}

		PIC24_Write(p, u_addr, &fw_data[page * fam->page_size], fam->page_size); //&fw_data[page * fam->page_size]

		//usleep(fam->write_delay * 1000);

		done += fam->page_size;
	}

    PIC24_ExitICSP(p, fam->icsp_type);

	return done;
}

uint32_t PIC24_ReadFlash(struct picprog_t *p, uint8_t *fw_data)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *fam = PIC_GetFamily(pic->family);
    struct iface_t *iface = p->iface;
    void *opts = p->iface_data;

	uint32_t u_addr;
	uint32_t page  = 0;
	uint32_t done  = 0, ctr;
    //uint8_t temp[pic->flash];
    uint32_t i;
    uint16_t r;
    uint8_t buf[8];

    PIC24_EnterICSP(p, fam->icsp_type);

	for (page = 0; page < pic->flash / fam->page_size; page++)
	{
		u_addr = page * fam->page_size;
		//( PIC_NUM_WORDS_IN_ROW * 2 * PIC_NUM_ROWS_IN_PAGE );
		//u_addr = page * ( 2 * 32 );

		if (u_addr >= pic->flash) {
			fprintf(stderr, "Address out of flash\n");
			continue;
		}

		printf("Reading page %ld, %04lx... \n", (unsigned long)page, (unsigned long)u_addr);

		//PIC24_Read(p, u_addr, &temp[page * fam->page_size], fam->page_size);
        iface->PIC424Write(opts, 0x200000 | ((u_addr & 0xffff0000) >> 12), 0, 0);//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
        iface->PIC424Write(opts, 0x880190, 0, 0);//SIX,0x880190,5, N/AMOV W0, TBLPAG
        iface->PIC424Write(opts, 0x200006 | ((u_addr & 0x000ffff) << 4), 0, 2);//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6
        iface->PIC424Write(opts, 0x207847, 0, 1);//SIX,0x200007,5, N/A  //MOV #VISI,W7 //PIC24NOP();//SIX,0x000000,5, N/A
        iface->flush(opts);

        for(i=0; i<fam->page_size; i=i+8){
            /*
             //X10
            //2XX/3XX
            //X54
            iface->PIC424Read(opts, 0xBA0B96, &r, 2);
            fw_data[(page * fam->page_size)+i]=(uint8_t)r;
            fw_data[(page * fam->page_size)+i+1]=(uint8_t)(r>>8);

            iface->PIC424Write(opts, 0xBADBB6, 0, 2);//SIX,0x200007,5, N/A  //MOV #VISI,W7 //PIC24NOP();//SIX,0x000000,5, N/A
            iface->flush(opts);
            iface->PIC424Read(opts, 0xBAD3D6, &r, 2);
            fw_data[(page * fam->page_size)+i+2]=r;
            fw_data[(page * fam->page_size)+i+6]=(uint8_t)(r>>8);

            iface->PIC424Read(opts, 0xBA0BB6, &r, 2);
            fw_data[(page * fam->page_size)+i+4]=r;
            fw_data[(page * fam->page_size)+i+5]=(uint8_t)(r>>8);

            fw_data[(page * fam->page_size)+i+3]=0x00;
            fw_data[(page * fam->page_size)+i+7]=0x00;
            */

                         //X10
            //2XX/3XX
            //X54
            iface->PIC424Read(opts, 0xBA0B96, &buf, 1);//read one 2 word chunk
            fw_data[(page * fam->page_size)+i]=buf[0];
            fw_data[(page * fam->page_size)+i+1]=buf[1];

            fw_data[(page * fam->page_size)+i+2]=buf[2];
            fw_data[(page * fam->page_size)+i+6]=buf[3];

            fw_data[(page * fam->page_size)+i+4]=buf[4];
            fw_data[(page * fam->page_size)+i+5]=buf[5];

            fw_data[(page * fam->page_size)+i+3]=0x00;
            fw_data[(page * fam->page_size)+i+7]=0x00;
        }

        PIC24NOP();//SIX,0x000000,5, N/A
        iface->PIC424Write(opts, 0x040200, 0, 2);
        iface->flush(opts);

		if (p->debug) {
			dumpHex(&fw_data[page * fam->page_size], fam->page_size);
		}

		//usleep(fam->write_delay * 1000);

		done += fam->page_size;
	}

   PIC24_ExitICSP(p, fam->icsp_type);

/*
    for(ctr=0; ctr<(pic->flash); ctr=ctr+16){
        //X10
        //2XX/3XX
        //X54
        (((uint8_t *)fw_data)[(ctr)])=temp[ctr];
        (((uint8_t *)fw_data)[(ctr)+1])=temp[(ctr)+1];
        (((uint8_t *)fw_data)[(ctr)+2])=temp[(ctr)+3];
        (((uint8_t *)fw_data)[(ctr)+3])=0x00;
        (((uint8_t *)fw_data)[(ctr)+4])=temp[(ctr)+5];
        (((uint8_t *)fw_data)[(ctr)+5])=temp[(ctr)+4];
        (((uint8_t *)fw_data)[(ctr)+6])=temp[(ctr)+2];
        (((uint8_t *)fw_data)[(ctr)+7])=0x00;
        (((uint8_t *)fw_data)[(ctr)+8])=temp[(ctr)+7];
        (((uint8_t *)fw_data)[(ctr)+9])=temp[(ctr)+6];
        (((uint8_t *)fw_data)[(ctr)+10])=temp[(ctr)+9];
        (((uint8_t *)fw_data)[(ctr)+11])=0x00;
        (((uint8_t *)fw_data)[(ctr)+12])=temp[(ctr)+11];
        (((uint8_t *)fw_data)[(ctr)+13])=temp[(ctr)+10];
        (((uint8_t *)fw_data)[(ctr)+14])=temp[(ctr)+8];
        (((uint8_t *)fw_data)[(ctr)+15])=0x00;
    }
*/
	return done;
}

