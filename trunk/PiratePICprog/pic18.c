
#include <unistd.h>

#include "pic.h"
#include "iface.h"
#include "pic18.h"

static uint8_t writesetup=0;

uint32_t PIC18_EnterICSP(struct picprog_t *p, enum icsp_t type) {
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	uint8_t buffer[4], i, j, r;

	//for
	if(type==ICSP_HVPP){
		iface->MCLRLow(opts);
		//iface->MCLRHVP(opts);
        return 0;
	}

	//all programming operations are LSB first, but the ICSP entry key is MSB first.
	// Reconfigure the mode for LSB order
	//pritf("Set mode for MCLR (MSB)...");

	//iface->SetBitOrder(opts, BIT_MSB);

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

uint32_t PIC18_ExitICSP(struct picprog_t *p){
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;

	//exit programming mode
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
	usleep(1000 * f->erase_delay);

	PIC18_ExitICSP(p);

	return 0;
}

uint32_t PIC18_ReadID(struct picprog_t *p, uint16_t *id, uint16_t *rev){
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint32_t PICid;

    PIC18_EnterICSP(p, f->icsp_type);

	//setup read from device ID bits
	PIC18_settblptr(p, f->ID_addr);

	//read device ID, two bytes takes 2 read operations, each gets a byte
	PICid = iface->PIC416Read(opts, 0x09);	//lower 8 bits
	PICid |= iface->PIC416Read(opts, 0x09) << 8;	//upper 8 bits

    PIC18_ExitICSP(p);

    //determine device type
	*rev=(PICid&(~0xFFE0)); //find PIC ID (lower 5 bits)
	*id=(PICid>>5); //isolate PIC device ID (upper 11 bits)

	return PICid;
}

uint32_t PIC18_Read(struct picprog_t *p, uint32_t tblptr, void *Data, uint32_t length)
{
	struct iface_t *iface = p->iface;
	void *opts = p->iface_data;
	uint32_t ctr;

	//setup read
	PIC18_settblptr(p, tblptr);
	//read device
	for (ctr = 0; ctr < length; ctr++)
	{
		//printf("%X ", PIC416Read(0x09) );
		((uint8_t*)Data)[ctr] = iface->PIC416Read(opts, 0x09);
	}

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

	return 0;
}



