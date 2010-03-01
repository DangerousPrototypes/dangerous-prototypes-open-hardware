#ifndef __COMPILER_H__
#define __COMPILER_H__

#ifdef __IMAGECRAFT__


// choose your AVR device here
#include <iom128v.h>

#include <macros.h>

#define outp(val, reg)  (reg = val)
#define inp(reg)        (reg)

#define cli()           CLI()
#define sei()           SEI()
#define cbi(reg, bit)   (reg &= ~BIT(bit))
#define sbi(reg, bit)   (reg |= BIT(bit))

#define SIGNAL(x)       void x(void)  

#define nop() NOP()

#define _BV(x)	   (1<<x)


#else /* --- GCC --- */

//#include <avr/signal.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define outp(val, reg)  (reg = val)
#define inp(reg)        (reg)

#define cbi(p, q) ((p) &= ~_BV(q))
#define sbi(p, q) ((p) |= _BV(q))

#define nop() asm volatile("nop\n\t"::);

#endif /* Compiler Used */

typedef unsigned char u8;
typedef unsigned short u16;

#endif /* __COMPILER_H__ */

