
#include <unistd.h>
#include <stdio.h>
#include "pic.h"
#include "iface.h"
#include "pic18.h"

static uint8_t writesetup=0;

static uint32_t PIC18_Read_Fuse(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length);
static uint32_t PIC18_Read_Flash(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length);
static uint32_t PIC18_Read_EEPROM(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length);
static uint32_t PIC18_Write_Fuse(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length);
static uint32_t PIC18_Write_Flash(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length);
static uint32_t PIC18_Write_EEPROM(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length);

static uint32_t PIC18_EnterICSP(struct picprog_t *p, enum icsp_t type)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;

	char buffer[4];

	iface->VCCHigh();

	iface->ClockLow();
	iface->DataLow();
	//AUX low...

	//for
	if (type == ICSP_HVPP) {
		//a transistor is connected so this is opposite
		iface->MCLRHigh();//makes 0
		iface->MCLRLow(); //lets go high
		iface->MCLRHigh(); //makes 0

		iface->VPPHigh(); //AUX high to apply 13V (CS=1)
		iface->MCLRLow(); //MCLR low to bring MCLR to 13volts
		return 0;
	}

	//all programming operations are LSB first, but the ICSP entry key is MSB first.
	// Reconfigure the mode for LSB order
	//pritf("Set mode for MCLR (MSB)...");

	//iface->SetBitOrder(BIT_LSB);
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
	return 0;
}

static uint32_t PIC18_ExitICSP(struct picprog_t *p, enum icsp_t type)
{
	struct iface_t *iface = p->iface;

	//exit programming mode

	if (type == ICSP_HVPP) {
		//a transistor is connected so this is opposite
		iface->VPPLow(); //Turn off AUX, remove 13V (CS=1)
		//iface->MCLRHigh();//makes 0
		iface->MCLRLow(); //lets go high

		iface->VCCLow();
		return 0;
	}

	iface->MCLRLow();
	iface->MCLRHigh();

	iface->VCCLow();
	return 0;
}

static void PIC18_settblptr(struct picprog_t *p, uint32_t tblptr)
{
	struct iface_t *iface = p->iface;

	// set TBLPTR
	iface->PIC416Write(0x00, 0x0E00 | ((tblptr >> 16) & 0xff));
	iface->PIC416Write(0x00, 0x6EF8);
	iface->PIC416Write(0x00, 0x0E00 | ((tblptr >> 8) & 0xff));
	iface->PIC416Write(0x00, 0x6EF7);
	iface->PIC416Write(0x00, 0x0E00 | ((tblptr) & 0xff));
	iface->PIC416Write(0x00, 0x6EF6);
}

//erase 18F, sleep delay should be adjustable
static uint32_t PIC18_Erase(struct picprog_t *p)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;

	PIC18_EnterICSP(p, f->icsp_type);

	PIC18_settblptr(p, 0x3C0005); //set pinter to erase register
	iface->PIC416Write(0x0C, f->erase_key[0]);//write special erase token
	PIC18_settblptr(p, 0x3C0004); //set pointer to second erase register
	iface->PIC416Write(0x0C, f->erase_key[1]);//write erase command
	iface->PIC416Write(0, 0);
	iface->PIC416Write(0, 0);
	iface->flush();
	usleep(1000 * f->erase_delay);

	PIC18_ExitICSP(p, f->icsp_type);

	return 0;
}

static uint32_t PIC18_ReadID(struct picprog_t *p, uint32_t *id, uint16_t *rev)
{
	struct pic_chip_t *pic = PIC_GetChip(p->chip_idx);
	struct pic_family_t *f = PIC_GetFamily(pic->family);
	struct iface_t *iface = p->iface;
	uint32_t PICid;
	unsigned char buffer[2];

	PIC18_EnterICSP(p, f->icsp_type);

	//setup read from device ID bits
	PIC18_settblptr(p, f->ID_addr);
	iface->flush();
	//read device ID, two bytes takes 2 read operations, each gets a byte
	iface->PIC416Read(0x09, buffer, 2 );	//lower 8 bits
	iface->GetData(buffer, 2);

	PIC18_ExitICSP(p, f->icsp_type);

	PICid = buffer[0];
	PICid |= (buffer[1] << 8);

	//determine device type
	*rev = (PICid & (~0xFFE0)); //find PIC ID (lower 5 bits)
	*id = (PICid >> 5); //isolate PIC device ID (upper 11 bits)

	return PICid;
}

//a few things need to be done once at the beginning of a sequence of write operations
//this configures the PIC, and enables page writes
//call it once, then call PIC18F_write() as needed
static void PIC18_setupwrite(struct picprog_t *p)
{
	struct iface_t *iface = p->iface;

	iface->PIC416Write(0x00, 0x8EA6); //setup PIC
	iface->PIC416Write(0x00, 0x9CA6); //setup PIC
	iface->PIC416Write(0x00, 0x84A6); //enable page writes
}

pic_rw_func write_mem_table[PIC_MEM_LAST] = {
	[PIC_MEM_FUSE] = PIC18_Write_Fuse,
	[PIC_MEM_FLASH] = PIC18_Write_Flash,
	[PIC_MEM_EEPROM] = PIC18_Write_EEPROM
};

pic_rw_func read_mem_table[PIC_MEM_LAST] = {
	[PIC_MEM_FUSE] = PIC18_Read_Fuse,
	[PIC_MEM_FLASH] = PIC18_Read_Flash,
	[PIC_MEM_EEPROM] = PIC18_Read_EEPROM
};


//18F setup write location and write length bytes of data to PIC
static uint32_t PIC18_Write(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length)
{
	struct pic_memmap_t *m = (struct pic_memmap_t *)pic_chip[p->chip_idx].memmap;
	pic_rw_func fnc;
	int i;


	for (i = PIC_MEM_FUSE; i < PIC_MEM_LAST; i++) {
		if ((tblptr >= m[i].base) && (tblptr < (m[i].base + m[i].size))) {
			fnc = write_mem_table[i];
			if (fnc != NULL) {
				return fnc(p, tblptr, data, length);
			} else {
				printf("Unimplemented write to mem_type %d\n", i);
				return 0;
			}
		}
	}

	return 0; // ERROR!
}

static uint32_t PIC18_Read(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length)
{
	struct pic_memmap_t *m = (struct pic_memmap_t *)pic_chip[p->chip_idx].memmap;
	pic_rw_func fnc;
	int i;


	for (i = PIC_MEM_FUSE; i < PIC_MEM_LAST; i++) {
		if ((tblptr >= m[i].base) && (tblptr < (m[i].base + m[i].size))) {
			fnc = read_mem_table[i];
			if (fnc != NULL) {
				return fnc(p, tblptr, data, length);
			} else {
				printf("Unimplemented read from mem_type %d\n", i);
				return 0;
			}
		}
	}

	return 0; // ERROR!
}

// Fuse is the same as Flash for reads.
static uint32_t PIC18_Read_Fuse(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length)
{
	return PIC18_Read_Flash(p, tblptr, data, length);
}

static uint32_t PIC18_Read_Flash(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length)
{
	struct iface_t *iface = p->iface;
	//uint32_t ctr;

	//setup read
	PIC18_settblptr(p, tblptr);
	iface->flush();

	//read device
	iface->PIC416Read(0x09, data, length);

	iface->GetData(data, length);

	return 0;
}

static uint32_t PIC18_Read_EEPROM(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length)
{
	return 0; // unimplemented yet!
}

static uint32_t PIC18_Write_Fuse(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length)
{
	struct iface_t *iface = p->iface;
	uint16_t databyte;//, buffer[2]={0x00,0x00};
	uint32_t ctr;

	if (writesetup != PIC_MEM_FUSE) {
		iface->PIC416Write(0x00, 0x8EA6); //setup PIC - BSF   EECON1, EEPGD
		iface->PIC416Write(0x00, 0x8CA6); //setup PIC - BSF   EECON1, CFGS
		//iface->PIC416Write(0x00, 0x84A6); //enable page writes -
		writesetup = PIC_MEM_FUSE;
	}

	// set TBLPTR
	PIC18_settblptr(p, tblptr);

	for(ctr = 0; ctr < length; ctr++) {
		if ((ctr & 1) == 0)
			databyte = (((uint8_t *)data)[ctr + 1] << 8) + ((uint8_t *)data)[ctr];
		iface->PIC416Write(0x00, 0x0E00 | ctr);
		iface->PIC416Write(0x00, 0x6EF6);
		iface->PIC416Write(0x0F, databyte);
		iface->PIC416Write(0x40, 0x0000); // see PIC18_Write_Flash below
		iface->flush();
	}

	return 0;
}

static uint32_t PIC18_Write_Flash(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length)
{
	struct iface_t *iface = p->iface;
	uint16_t databyte;//, buffer[2]={0x00,0x00};
	uint32_t ctr;

	if (writesetup != PIC_MEM_FLASH) {
		PIC18_setupwrite(p);
		writesetup = PIC_MEM_FLASH;
	}

	// set TBLPTR
	PIC18_settblptr(p, tblptr);

	//PIC416Write(0x00,0x6AA6); //doesn't seem to be needed now
	//PIC416Write(0x00,0x88A6);
	iface->PIC416Write(0x00, 0x6AA6);
	iface->PIC416Write(0x00, 0x88A6);

	for(ctr = 0; ctr < length - 2; ctr += 2) {
		databyte = (((uint8_t *)data)[ctr + 1] << 8) + ((uint8_t *)data)[ctr];
		iface->PIC416Write(0x0D, databyte);
	}

	databyte = ((uint8_t *)data)[length - 1];
	databyte = databyte << 8;
	databyte |= ((uint8_t *)data)[length - 2];
	iface->PIC416Write(0x0F, databyte);

	//delay the 4th clock bit of the 20bit command to allow programming....
	//use upper bits of 4bit command to configure the delay
	//18f24j50 needs 1.2ms, lower parts in same family need 3.2
	iface->PIC416Write(0x40, 0x0000);

	iface->flush();

	return 0;
}

static uint32_t PIC18_Write_EEPROM(struct picprog_t *p, uint32_t tblptr, void *data, uint32_t length)
{
	return 0;
}

struct proto_ops_t pic18_proto = {
	.type = PROTO_PIC18,
	.EnterICSP = PIC18_EnterICSP,
	.ExitICSP = PIC18_ExitICSP,
	.ReadID = PIC18_ReadID,
	.Read = PIC18_Read,
	.Write = PIC18_Write,
	.Erase = PIC18_Erase
};
