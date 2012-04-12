#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "pic.h"
#include "iface.h"
#include "pic32.h"


#define PIC32NOP()   iface->PIC424Write(0x000000,0,0)

static uint32_t PIC32_Read(struct picprog_t *p, uint32_t addr, void* Data, uint32_t length);

static uint32_t PIC32_EnterICSP(struct picprog_t *p, enum icsp_t type)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	char buffer[4];

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

	// p7(500ns)+p17(100ns) 600ns delay before any data for pic32

	#ifdef OLD // Exits reset??
	//first 9bit SIX command, setup the PIC ICSP
	iface->SendBits(5, 0x00);//extra clocks
	iface->PIC424Write(0x040200, 0, 0);
	iface->PIC424Write(0x040200, 0, 3);//SIX,0x040200,5, NOP
	iface->PIC424Write(0x040200, 0, 1);//SIX,0x040200,5, goto 0x200
	#endif // OLD
	iface->flush();
	return 0;
}

static uint32_t PIC32_ExitICSP(struct picprog_t *p, enum icsp_t type)
{
	struct iface_t *iface = p->iface;

	//exit programming mode
	iface->MCLRLow();
	iface->MCLRHigh();
	return 0;
}

static uint32_t PIC32_ReadID(struct picprog_t *p, uint32_t *id, uint16_t *rev)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	uint32_t PICid;
	uint8_t buf[6];

	PIC32_EnterICSP(p, f->icsp_type);

	PIC32_Read(p, 0xBF80F220, &buf, 1);

	PIC32_ExitICSP(p, f->icsp_type);

	PICid = (buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24));

	*rev = (uint16_t)(PICid >> 28);
	// crc mask is 0x0FFFF000
	*id = (PICid & (~0xF0000FFF));

	//return (buf[0] | (buf[1] << 8));
	return(*id);
}

static uint32_t PIC32_Read(struct picprog_t *p, uint32_t addr, void* Data, uint32_t length)
{
	struct iface_t *iface = p->iface;

	//Step1
	iface->PIC424Write(0x3c04bf80,0,0);
	//Step2
	iface->PIC424Write(0x3c08 << 16 | addr >> 16,0,0);
	iface->PIC424Write(0x3508 << 16 | (addr & (~0xFFFF0000)),0,0);
	//Step3
	iface->PIC424Write(0x8d090000,0,0);
	iface->PIC424Write(0xae690000,0,0);
	//Step4
	iface->PIC424Read(0xFF200000, Data, length);
#ifdef OLD
	//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
	iface->PIC424Write(0x200000 | ((addr & 0xffff0000) >> 12), 0, 0);
	//SIX,0x880190,5, N/AMOV W0, TBLPAG
	iface->PIC424Write(0x880190, 0, 0);
	//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6
	iface->PIC424Write(0x200006 | ((addr & 0x000ffff) << 4), 0, 2);
	//SIX,0x200007,5, N/A  //MOV #VISI,W7
	iface->PIC424Write(0x207847, 0, 1);
	//PIC24NOP();//SIX,0x000000,5, N/A
	iface->flush();

	iface->PIC424Read(0xBA0BB6, Data, length);

	PIC32NOP();//SIX,0x000000,5, N/A
	iface->PIC424Write(0x040200, 0, 2);
	iface->flush();
#endif // OLD

	return 0;
}

struct ramflash_map_t {
	uint16_t ram;
	uint32_t flash;
};
static uint32_t PIC32_Write(
	struct picprog_t *p
	, uint32_t tblptr
	, void *Data, uint32_t length)
{
	struct iface_t *iface = p->iface;
	uint32_t ctr;

	//Write row to ram..
	uint8_t  dCur   = 0;
	uint32_t rBase  = 0xA0000000;
	uint32_t oCur   = 0;	// step rate 4
	uint32_t fCur   = tblptr; // step rate 1
	uint8_t rowsize = 32;
	struct ramflash_map_t  mapRamFlash[length];
	memset(mapRamFlash,0,sizeof(mapRamFlash));
	int cnt = 0;
	for(;cnt < rowsize;cnt++)
	{
	dCur = ((uint8_t*)Data)[cnt];
	//Step1
	iface->PIC424Write(0x3c10a000,0,0);
	//Step2
	iface->PIC424Write(0x3c08 << 16| (dCur >> 16 ),0,0);
	iface->PIC424Write(0x3508 << 16| (dCur & (~0xFFFF0000) ),0,0);
	iface->PIC424Write(0xae08 << 16| oCur,0,0);
	mapRamFlash[cnt].ram = oCur;
	mapRamFlash[cnt].flash = fCur;
	oCur += 4;
	fCur += 1;
	}
#if 0
	for(;cnt >= 0;cnt--)
	{
	// Transfer from ram to flash.
	// Step1
	iface->PIC424Write(0x3c04bf80,0,0);
	iface->PIC424Write(0x3484f400,0,0);
	iface->PIC424Write(0x34054003,0,0);
	iface->PIC424Write(0x34068000,0,0);
	iface->PIC424Write(0x34074000,0,0);
	iface->PIC424Write(0x3c11aa99,0,0);
	iface->PIC424Write(0x36316655,0,0);
	iface->PIC424Write(0x3c125566,0,0);
	iface->PIC424Write(0x365299aa,0,0);
	iface->PIC424Write(0x3c13ff20,0,0);
	iface->PIC424Write(0x3c100000,0,0);
	//Step2
	// FIXME
	//unsigned int addr = 0xFEAFBEED; // Flash addr
	unsigned int addr = mapRamFlash[cnt].flash;
	// base addr(0xA0000000) + offset(from section12, download data ??)
	//unsigned int ramAddr = 0xFEFE;  // Ram addr
	unsigned int ramAddr = rBase + mapRamFlash[cnt].ram;  // Ram addr
	iface->PIC424Write(0x3c08 << 16 | addr >> 16, 0,0);
	iface->PIC424Write(0x3508 << 16 | addr & (~0x0000FFFF),0,0);
	iface->PIC424Write(0xac880020,0,0);
	//Step3
	iface->PIC424Write(0x3610 << 16 | ramAddr, 0,0);
	//Step4
	iface->PIC424Write(0xac850000,0,0);
	iface->PIC424Write(0x8c880000,0,0);
	iface->PIC424Write(0x31080800,0,0);
	iface->PIC424Write(0x1500fffd,0,0);
	iface->PIC424Write(0,0,0);
	//Step5
	iface->PIC424Write(0xac910010,0,0);
	iface->PIC424Write(0xac920010,0,0);
	iface->PIC424Write(0xac860008,0,0);
	//Step6
	iface->PIC424Write(0x8c880000,0,0);
	iface->PIC424Write(0x01064204,0,0);
	iface->PIC424Write(0x1500fffd,0,0);
	iface->PIC424Write(0,0,0);
	//Step7
	for(char delay = 0; delay < 5;delay++)
		iface->PIC424Write(0,0,0); // 500ns @ 8MHz
	//Step8
	iface->PIC424Write(0xac870004,0,0);
	//Step9
	// FIXME err_proc_offset ??
	//iface->PIC424Write(0x8c880000,0,0);
	//iface->PIC424Write(0x30082000,0,0);
	//iface->PIC424Write(0x1500 << 16 | err_proc_offset,0,0);
	//iface->PIC424Write(0,0,0);
	}
#endif // NEVER

#ifdef OLD
	//Step2
	//set NVMCON
	iface->PIC424Write(0x24001A, 0, 0); //MOV XXXX,W10 0x4001 (differs by PIC)
	iface->PIC424Write(0x883B0A, 0, 0); //MOV W10,NVMCON
	tblptr=tblptr/2;

	//Step3
	//setup the table pointer
	iface->PIC424Write(0x200000 | ((tblptr & 0xffff0000) >> 12), 0, 0);//SIX,0x200FF0,5, N/A MOV #<SourceAddress23:16>, W0
	iface->PIC424Write(0x880190, 0, 1);//SIX,0x880190,5, N/AMOV W0, TBLPAG
	iface->PIC424Write(0x200007 | ((tblptr & 0x000ffff) << 4), 0, 2);//SIX,0x200006,5, N/A MOV #<SourceAddress15:0>, W6

	//Step4&5
	for(ctr = 0; ctr < 16; ctr++) { //really this is fixed at 16
		iface->PIC424Write(
			0x200000
			| ((((uint8_t *)Data)[(ctr*16)+1]) << 12)
			| ((((uint8_t *)Data)[(ctr*16)])<< 4)
		, 0, 0);
		iface->PIC424Write(
			0x200001
			| ((((uint8_t *)Data)[(ctr*16)+6])<< 12)
			|((((uint8_t *)Data)[(ctr*16)+2])<< 4)
		, 0, 0);
		iface->PIC424Write(
			0x200002
			| ((((uint8_t *)Data)[(ctr*16)+5])<< 12)
			|((((uint8_t *)Data)[(ctr*16)+4])<< 4)
		, 0, 0);
		iface->PIC424Write(
			0x200003
			| ((((uint8_t *)Data)[(ctr*16)+9])<< 12)
			| ((((uint8_t *)Data)[(ctr*16)+8])<< 4)
		, 0, 0);
		iface->PIC424Write(
			0x200004
			| ((((uint8_t *)Data)[(ctr*16)+14])<< 12)
			| ((((uint8_t *)Data)[(ctr*16)+10])<< 4)
		, 0, 0);
		iface->PIC424Write(
			0x200005
			| ((((uint8_t *)Data)[(ctr*16)+13])<< 12)
			| ((((uint8_t *)Data)[(ctr*16)+12])<< 4)
		, 0, 0);

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
	PIC32NOP();//SIX,0x000000,5, N/A
	iface->PIC424Write(0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)
	iface->flush();
	usleep(3000);
		//if(!(VISI & 0x8000)) break; //bit15 will clear when erase is done
	//}
#endif // OLD
	return 0;
}

static uint32_t PIC32_Erase(struct picprog_t *p)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	//uint16_t VISI;

	PIC32_EnterICSP(p, f->icsp_type);

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
	PIC32NOP();//SIX,0x000000,5, N/A
	iface->PIC424Write(0x040200, 0, 2);//SIX,0xBA0BB6,5, N/A TBLRDH.B [W6++], [W7++] (this needs a pre-NOP)
	iface->flush();

		//if(!(VISI & 0x8000)) break; //bit15 will clear when erase is done
	usleep(1000 * f->erase_delay);
	//}

	PIC32_ExitICSP(p, f->icsp_type);

	return 0;
}

struct proto_ops_t pic32_proto = {
	.type = PROTO_PIC32,
	.EnterICSP = PIC32_EnterICSP,
	.ExitICSP = PIC32_ExitICSP,
	.ReadID = PIC32_ReadID,
	.Read = PIC32_Read,
	.Write = PIC32_Write,
	.Erase = PIC32_Erase,
};

//////////////
static uint32_t PIC32_Setmode(struct picprog_t *p,unsigned char modelen, unsigned char newmode)
{

}


