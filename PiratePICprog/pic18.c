
#include <unistd.h>
#include <stdio.h>
#include "pic.h"
#include "iface.h"
#include "pic18.h"

static uint8_t writesetup=0;

uint32_t PIC18_EnterICSP(struct picprog_t *p, enum icsp_t type) {
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	uint8_t buffer[4];

	iface->ClockLow(opts);
	iface->DataLow(opts);
	//AUX low...

	//for
	if(type==ICSP_HVPP){
	    //a transistor is connected so this is opposite
        iface->MCLRHigh(opts);//makes 0
	    iface->MCLRLow(opts); //lets go high
        iface->MCLRHigh(opts); //makes 0

        iface->VPPHigh(opts); //AUX high to apply 13V (CS=1)
        iface->MCLRLow(opts); //MCLR low to bring MCLR to 13volts
        return 0;
	}

	//all programming operations are LSB first, but the ICSP entry key is MSB first.
	// Reconfigure the mode for LSB order
	//pritf("Set mode for MCLR (MSB)...");

	//iface->SetBitOrder(opts, BIT_LSB);
	iface->MCLRLow(opts);
	iface->MCLRHigh(opts);
	iface->MCLRLow(opts);

//send ICSP key 0x4D434850
	buffer[0] = f->icsp_key >> 24;
	buffer[1] = f->icsp_key >> 16;
	buffer[2] = f->icsp_key >> 8;
	buffer[3] = f->icsp_key;

  //reverse the bits in the PC so we save asking the PIC to do it...
  /*
    for(j=0; j<4; j++){
        for(i=0b1; i!=0; i=i<<1){
            r=r<<1;
            if(buffer[j]&i)r|=0b1;
        }
        buffer[j]=r;
    }
*/
	iface->SendBytes(opts, 4, buffer);
	iface->DataLow(opts);
	iface->MCLRHigh(opts);

	//all programming operations are LSB first, but the ICSP entry key is MSB first.
	// Reconfigure the mode for LSB order
	//printf("Set mode for PIC programming (LSB)...");

	//iface->SetBitOrder(opts, BIT_LSB);

	//puts("(OK)");
	return 0;
}

uint32_t PIC18_ExitICSP(struct picprog_t *p, enum icsp_t type){
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	//exit programming mode

	if(type==ICSP_HVPP){
	    //a transistor is connected so this is opposite
        iface->VPPLow(opts); //Turn off AUX, remove 13V (CS=1)
        //iface->MCLRHigh(opts);//makes 0
	    iface->MCLRLow(opts); //lets go high
        return 0;
	}

	iface->MCLRLow(opts);
	iface->MCLRHigh(opts);
	return 0;
}

static void PIC18_settblptr(struct picprog_t *p, uint32_t tblptr)
{
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	// set TBLPTR
	iface->PIC416Write(opts, 0x00, 0x0E00 | ((tblptr >> 16) & 0xff));
	iface->PIC416Write(opts, 0x00, 0x6EF8);
	iface->PIC416Write(opts, 0x00, 0x0E00 | ((tblptr >> 8) & 0xff));
	iface->PIC416Write(opts, 0x00, 0x6EF7);
	iface->PIC416Write(opts, 0x00, 0x0E00 | ((tblptr) & 0xff));
	iface->PIC416Write(opts, 0x00, 0x6EF6);
}

//erase 18F, sleep delay should be adjustable
uint32_t PIC18_Erase(struct picprog_t *p) {
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

    PIC18_EnterICSP(p, f->icsp_type);

	PIC18_settblptr(p, 0x3C0005); //set pinter to erase register
	iface->PIC416Write(opts, 0x0C, f->erase_key[0]);//write special erase token
	PIC18_settblptr(p, 0x3C0004); //set pointer to second erase register
	iface->PIC416Write(opts, 0x0C, f->erase_key[1]);//write erase command
	iface->PIC416Write(opts, 0, 0);
	iface->PIC416Write(opts, 0, 0);
	iface->flush(opts);
	usleep(1000 * f->erase_delay);

	PIC18_ExitICSP(p, f->icsp_type);

	return 0;
}

uint32_t PIC18_ReadID(struct picprog_t *p, uint16_t *id, uint16_t *rev){
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint32_t PICid;
	unsigned char buffer[2];

    PIC18_EnterICSP(p, f->icsp_type);

	//setup read from device ID bits
	PIC18_settblptr(p, f->ID_addr);
	iface->flush(opts);
	//read device ID, two bytes takes 2 read operations, each gets a byte
	iface->PIC416Read(opts, 0x09, buffer, 2 );	//lower 8 bits

    PIC18_ExitICSP(p, f->icsp_type);

    PICid=buffer[0];
    PICid|=(buffer[1]<<8);

    //determine device type
	*rev=(PICid&(~0xFFE0)); //find PIC ID (lower 5 bits)
	*id=(PICid>>5); //isolate PIC device ID (upper 11 bits)

	return PICid;
}

uint32_t PIC18_Read(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length)
{
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	//uint32_t ctr;

	//setup read
	PIC18_settblptr(p, tblptr);
    iface->flush(opts);
	//read device
	iface->PIC416Read(opts, 0x09, Data, length);

//	for (ctr = 0; ctr < length; ctr++)
//	{
//		//printf("%X ", PIC416Read(0x09) );
//		((uint8_t*)Data)[ctr] = iface->PIC416Read(opts, 0x09);
//	}

	return 0;
}

//a few things need to be done once at the beginning of a sequence of write operations
//this configures the PIC, and enables page writes
//call it once, then call PIC18F_write() as needed
static void PIC18_setupwrite(struct picprog_t *p) {
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	iface->PIC416Write(opts, 0x00, 0x8EA6); //setup PIC
	iface->PIC416Write(opts, 0x00, 0x9CA6); //setup PIC
	iface->PIC416Write(opts, 0x00, 0x84A6); //enable page writes
}

//18F setup write location and write length bytes of data to PIC
uint32_t PIC18_Write(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length)
{
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint16_t DataByte;//, buffer[2]={0x00,0x00};
	uint32_t ctr;
//	uint8_t	buffer[4] = {0};

    if(writesetup==0){
        PIC18_setupwrite(p);
        writesetup=1;
    }

	// set TBLPTR
	PIC18_settblptr(p, tblptr);

	//PIC416Write(0x00,0x6AA6); //doesn't seem to be needed now
	//PIC416Write(0x00,0x88A6);
	iface->PIC416Write(opts, 0x00, 0x6AA6);
	iface->PIC416Write(opts, 0x00, 0x88A6);

	for(ctr = 0; ctr < length - 2; ctr += 2) {
		DataByte = ((uint8_t *)Data)[ctr + 1];
		DataByte = DataByte << 8;
		DataByte |= ((uint8_t *)Data)[ctr];
		iface->PIC416Write(opts, 0x0D, DataByte);
	}

	DataByte = ((uint8_t *)Data)[length - 1];
	DataByte = DataByte << 8;
	DataByte |= ((uint8_t *)Data)[length - 2];
	iface->PIC416Write(opts, 0x0F, DataByte);

	//delay the 4th clock bit of the 20bit command to allow programming....
	//use upper bits of 4bit command to configure the delay
	//18f24j50 needs 1.2ms, lower parts in same family need 3.2
	iface->PIC416Write(opts, 0x40, 0x0000);

    iface->flush(opts);

	return 0;
}

int PIC18_WriteFlash(struct picprog_t *p, uint8_t *fw_data)
{
	struct pic_family_t *fam = PIC_GetFamily(p->chip_idx);
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct proto_ops_t *proto = Proto_GetOps(fam->proto);
    //struct iface_t *iface = p->iface;

	uint32_t u_addr;
	uint32_t page  = 0;
	uint32_t done  = 0;
	uint8_t used = 0;
	uint16_t i = 0;//, ctr;

    proto->EnterICSP(p, fam->icsp_type);

	for (page = 0; page < pic->flash / fam->page_size; page++)
	{
		u_addr = page * fam->page_size;
		//( PIC_NUM_WORDS_IN_ROW * 2 * PIC_NUM_ROWS_IN_PAGE );
		//u_addr = page * ( 2 * 32 );

		// check used page
		used = 0;
		for (i = 0; i < fam->page_size; i++) {

           //t=fw_data[u_addr+i];
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

		proto->Write(p, u_addr, &fw_data[page * fam->page_size], fam->page_size); //&fw_data[page * fam->page_size]

		//usleep(fam->write_delay * 1000);

		done += fam->page_size;
	}

    proto->ExitICSP(p, fam->icsp_type);

	return done;
}

int PIC18_ReadFlash(struct picprog_t *p, uint8_t *fw_data)
{
	struct pic_family_t *fam = PIC_GetFamily(p->chip_idx);
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct proto_ops_t *proto = Proto_GetOps(fam->proto);

	uint32_t u_addr;
	uint32_t page  = 0;
	uint32_t done  = 0;

    proto->EnterICSP(p, fam->icsp_type);

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

		proto->Read(p, u_addr, &fw_data[page * fam->page_size], fam->page_size);

//		if (p->debug) {
			dumpHex(&fw_data[page * fam->page_size], fam->page_size);
//		}

		//usleep(fam->write_delay * 1000);

		done += fam->page_size;
	}

    proto->ExitICSP(p, fam->icsp_type);

	return done;
}


