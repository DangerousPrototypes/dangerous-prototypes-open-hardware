#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "debug.h"
#include "pic.h"
#include "iface.h"
#include "pic24.h"


#define PIC24NOP()   iface->PIC424Write(0x000000,0,0)

static uint32_t PIC24_Read(struct picprog_t *p, uint32_t addr, void* Data, uint32_t length);

static uint32_t PIC24_EnterICSP(struct picprog_t *p, enum icsp_t type)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	char buffer[4];

	//all programming operations are LSB first, but the ICSP entry key is MSB first.
	// Reconfigure the mode for LSB order
	//printf("Set mode for MCLR (MSB)...");
	//iface->SetBitOrder(BIT_MSB);
	//puts("(OK)");

	iface->ClockLow();
	iface->DataLow();
	iface->MCLRLow();
	iface->MCLRHigh();
	iface->MCLRLow();

	//send ICSP key 0x4D434850
	buffer[0] = f->icsp_key >> 24;
	buffer[1] = f->icsp_key >> 16;
	buffer[2] = f->icsp_key >> 8;
	buffer[3] = f->icsp_key;

	iface->SendBytes(4, buffer);
	iface->DataLow();
	iface->MCLRHigh();

	//all programming operations are LSB first, but the ICSP entry key is MSB first.
	// Reconfigure the mode for LSB order
	//printf("Set mode for PIC programming (LSB)...");
	//iface->SetBitOrder(BIT_LSB);
	//puts("(OK)");

	//setup the Bus Pirate for 424 writes


	//first 9bit SIX command, setup the PIC ICSP
	iface->SendBits(5, 0x00);//five extra clocks on first SIX command after ICSP mode
	iface->PIC424Write(0x040200, 0, 0);
	iface->PIC424Write(0x040200, 0, 3);//SIX,0x040200,5, NOP
	iface->PIC424Write(0x040200, 0, 1);//SIX,0x040200,5, goto 0x200
	iface->flush();
	return 0;
}

static uint32_t PIC24_ExitICSP(struct picprog_t *p, enum icsp_t type)
{
	struct iface_t *iface = p->iface;

	//exit programming mode
	iface->MCLRLow();
	iface->MCLRHigh();
	return 0;
}

static uint32_t PIC24_ReadRaw(struct picprog_t *p, uint32_t addr, void* Data, uint32_t length)
{
	struct iface_t *iface = p->iface;

	iface->PIC424Write(0x200000 | ((addr & 0xffff0000) >> 12), 0, 0);//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
	iface->PIC424Write(0x880190, 0, 0);//SIX,0x880190,5, N/AMOV W0, TBLPAG
	iface->PIC424Write(0x200006 | ((addr & 0x000ffff) << 4), 0, 2);//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6
	iface->PIC424Write(0x207847, 0, 1);//SIX,0x200007,5, N/A  //MOV #VISI,W7 //PIC24NOP();//SIX,0x000000,5, N/A
	iface->flush();

	iface->PIC424Read(0xBA0BB6, Data, length);

	PIC24NOP();//SIX,0x000000,5, N/A
	iface->PIC424Write(0x040200, 0, 2);
	iface->flush();

	return 0;
}

static uint32_t PIC24_ReadID(struct picprog_t *p, uint32_t *id, uint16_t *rev)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
//	struct iface_t *iface = p->iface;
	uint32_t PICid;
	uint8_t buf[6];

	PIC24_EnterICSP(p, f->icsp_type);

	PIC24_ReadRaw(p, 0x00FF0000, &buf, 1); //give it the ID addres

	PIC24_ExitICSP(p, f->icsp_type);

	//PICid = (buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));
	PICid = (buf[1] | (buf[0] << 8) | (buf[3] << 16) | (buf[2] << 24));

	dbg_buf_info(buf, 6);
	//determine device type
	*rev = (uint16_t)(PICid >> 16); //find PIC ID (lower 16 bits)
	*id = (PICid & (~0xFFFF0000)); //isolate revision (upper 16 bits)

	return (buf[0] | (buf[1] << 8));
}

static uint32_t PIC24_Read(struct picprog_t *p, uint32_t addr, void* Data, uint32_t length)
{
	uint8_t buf[6];
	uint8_t *data = Data;
	uint32_t instr;

	instr = (length+7)/8; // number of instruction pairs (3bytes per instruction) 

	PIC24_ReadRaw(p, addr/2, Data + (instr*2), instr); // reads 2 instructions, packed

	// unpack instruction pairs
	for (uint32_t i = 0; i < instr; i ++) {
		memcpy(buf, Data + (instr*2) + (i*6), 6);

		// unpack according to DS
 		data[i*8+3] = 0;
		data[i*8+7] = 0;

		data[i*8+1] = buf[0];
		data[i*8+0] = buf[1];

		data[i*8+6] = buf[2];
		data[i*8+2] = buf[3];

		data[i*8+5] = buf[4];
		data[i*8+4] = buf[5];
	}

	return 0;
}

//18F setup write location and write length bytes of data to PIC
static uint32_t PIC24_Write(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length)
{
	struct iface_t *iface = p->iface;
//	uint16_t DataByte;//, buffer[2]={0x00,0x00};
	uint32_t ctr;//, tem, tem1;
//	uint8_t	buffer[4] = {0};
	//uint16_t VISI;

	//set NVMCON
	iface->PIC424Write(0x24001A, 0, 0); //MOV XXXX,W10 0x4001 (differs by PIC)
	iface->PIC424Write(0x883B0A, 0, 0); //MOV W10,NVMCON
	tblptr=tblptr/2;

	//setup the table pointer
	iface->PIC424Write(0x200000 | ((tblptr & 0xffff0000) >> 12), 0, 0);//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
	iface->PIC424Write(0x880190, 0, 1);//SIX,0x880190,5, N/AMOV W0, TBLPAG
	iface->PIC424Write(0x200007 | ((tblptr & 0x000ffff) << 4), 0, 2);//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6

	for(ctr = 0; ctr < 16; ctr++) { //really this is fixed at 16
		//iface->PIC424Write(0x200000 | ((((uint16_t *)Data)[ctr])<< 4), 0, 0); //MOV XXXX,W0 (0x0000) X10
		iface->PIC424Write(0x200000 | ((((uint8_t *)Data)[(ctr*16)+1])<< 12)|((((uint8_t *)Data)[(ctr*16)])<< 4), 0, 0);
	//	iface->PIC424Write(0x200001 | ((((uint16_t *)Data)[ctr+1])<< 4), 0, 0); //MOV XXXX,W1 (0x0000) 2XX/3XX
		iface->PIC424Write(0x200001 | ((((uint8_t *)Data)[(ctr*16)+6])<< 12)|((((uint8_t *)Data)[(ctr*16)+2])<< 4), 0, 0);
	//	iface->PIC424Write(0x200002 | ((((uint16_t *)Data)[ctr+2])<< 4), 0, 0); //MOV XXXX,W2(0x0000) X54
		iface->PIC424Write(0x200002 | ((((uint8_t *)Data)[(ctr*16)+5])<< 12)|((((uint8_t *)Data)[(ctr*16)+4])<< 4), 0, 0);
	//	iface->PIC424Write(0x200003 | ((((uint16_t *)Data)[ctr+3])<< 4), 0, 0); //MOV XXXX,W3 (0x0000)
		iface->PIC424Write(0x200003 | ((((uint8_t *)Data)[(ctr*16)+9])<< 12)|((((uint8_t *)Data)[(ctr*16)+8])<< 4), 0, 0);
	//	iface->PIC424Write(0x200004 | ((((uint16_t *)Data)[ctr+4])<< 4), 0, 0); //MOV XXXX,W4 (0x0000)
		iface->PIC424Write(0x200004 | ((((uint8_t *)Data)[(ctr*16)+14])<< 12)|((((uint8_t *)Data)[(ctr*16)+10])<< 4), 0, 0);
	//	iface->PIC424Write(0x200005 | ((((uint16_t *)Data)[ctr+5])<< 4), 0, 0); //MOV XXXX,W5 (0x0000)
		iface->PIC424Write(0x200005 | ((((uint8_t *)Data)[(ctr*16)+13])<< 12)|((((uint8_t *)Data)[(ctr*16)+12])<< 4), 0, 0);

		iface->PIC424Write(0xEB0300, 0, 1);//CLR W6
		iface->PIC424Write(0xBB0BB6, 0, 2);	//TBLWTL [W6++], [W7]
		iface->PIC424Write(0xBBDBB6, 0, 2);	//TBLWTH.B [W6++], [W7++]
		iface->PIC424Write(0xBBEBB6, 0, 2);	//TBLWTH.B [W6++], [++W7]
		iface->PIC424Write(0xBB1BB6, 0, 2); //TBLWTL [W6++], [W7++]
		iface->PIC424Write(0xBB0BB6, 0, 2);	//TBLWTL [W6++], [W7]
		iface->PIC424Write(0xBBDBB6, 0, 2);	//TBLWTH.B [W6++], [W7++]
		iface->PIC424Write(0xBBEBB6, 0, 2);	//TBLWTH.B [W6++], [++W7]
		iface->PIC424Write(0xBB1BB6, 0, 2);	//TBLWTL [W6++], [W7++]
	}

	//start the write cycle
	iface->PIC424Write(0xA8E761, 0, 2); //BSET NVMCON, #WR
	iface->flush();

	//repeat until write done, should reset counter every now and then too... 11000000 01001111
	//while(1) {
		//PIC24NOP();
		//iface->PIC424Write(0x803B02, 0, 2);//MOV NVMCON,W2
		//iface->PIC424Write(0x883C22, 0, 2);//MOV W2,VISI
		//iface->flush();

		//VISI = iface->PIC424Read(0xBA0BB6, Data, 1);//REGOUT,0x000000,5, read VISI register (PIC includes 2 NOPS after every read, may need to be updated later)
		//printf("Read: %X \n",VISI); //REGOUT,0x000000,5, read VISI register
	PIC24NOP();//SIX,0x000000,5, N/A
	iface->PIC424Write(0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)
	iface->flush();
	usleep(3000);
		//if(!(VISI & 0x8000)) break; //bit15 will clear when erase is done
	//}
	return 0;
}

static uint32_t PIC24_Erase(struct picprog_t *p)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	//uint16_t VISI;

	PIC24_EnterICSP(p, f->icsp_type);

	//set NVMCON
	iface->PIC424Write(0x2404FA, 0, 0); //MOV XXXX,W10 0x404F (differs by PIC)
	iface->PIC424Write(0x883B0A, 0, 0); //MOV W10,NVMCON

	// Step 3: Set TBLPAG
	iface->PIC424Write(0x200000, 0, 0); //MOV XXXX,W0 (0x0000)
	iface->PIC424Write(0x880190, 0, 1); //MOV W0,TABLPAG
	iface->PIC424Write(0xBB0800, 0, 2); //TBLWTL W0,[W0] (dummy write)

	iface->PIC424Write(0xA8E761, 0, 2); //BSET NVMCON,#WR
	//sleep(1);

	//repeat until erase done, should reset counter every now and then too... 11000000 01001111
	//while(1){
		//PIC24NOP();
		//iface->PIC424Write(0x803B02, 0, 2);//MOV NVMCON,W2
		//iface->PIC424Write(0x883C22, 0, 2);//MOV W2,VISI
        //iface->flush();

		//VISI = iface->PIC424Read();//REGOUT,0x000000,5, read VISI register (PIC includes 2 NOPS after every read, may need to be updated later)
		//printf("Read: %X \n",VISI); //REGOUT,0x000000,5, read VISI register
	PIC24NOP();//SIX,0x000000,5, N/A
	iface->PIC424Write(0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)
	iface->flush();

		//if(!(VISI & 0x8000)) break; //bit15 will clear when erase is done
	usleep(1000 * f->erase_delay);
	//}

	PIC24_ExitICSP(p, f->icsp_type);

	return 0;
}

struct proto_ops_t pic24_proto = {
	.type = PROTO_PIC24,
	.EnterICSP = PIC24_EnterICSP,
	.ExitICSP = PIC24_ExitICSP,
	.ReadID = PIC24_ReadID,
	.Read = PIC24_Read,
	.Write = PIC24_Write,
	.Erase = PIC24_Erase,
};
