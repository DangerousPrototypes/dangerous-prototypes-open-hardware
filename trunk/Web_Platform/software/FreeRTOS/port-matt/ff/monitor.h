/*------------------------------------------------------------------------*/
/* Universal string handler for user console interface  (C)ChaN, 2010     */
/*------------------------------------------------------------------------*/

#ifndef _STRFUNC
#define _STRFUNC

#define _USE_XFUNC_OUT	1	/* 1: Use output functions */
#define	_CR_CRLF		1	/* 1: Convert \n ==> \r\n in the output char */

#define _USE_XFUNC_IN	1	/* 1: Use input function */
#define	_LINE_ECHO		1	/* 1: Echo back input chars in get_line function */


#if _USE_XFUNC_OUT
extern void (*xfunc_out)(unsigned char);
void xputc (char);
void xputs (const char*);
void xprintf (const char*, ...);
void put_dump (const void*, unsigned long, int);
#endif

#if _USE_XFUNC_IN
extern unsigned char (*xfunc_in)(void);
int get_line (char*, int);
int xatoi (char**, long*);
#endif

#endif
