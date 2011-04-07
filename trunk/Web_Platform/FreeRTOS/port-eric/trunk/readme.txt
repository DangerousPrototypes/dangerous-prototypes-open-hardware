This is a port of FreeRTOS, uIP and FatFS to the Web Platform
=============================================================

Author               Date        Comment
=============================================================
Matt Callow			20101010	Initial File Creation
Eric Walker			20101112	Cleaned up main.c and layout,
								Fixed OSC PLL switching so it
					is now running at the correct speed, 
					Fixed OSC config for OSC2 pin RA3, Added 
					osc.c/h for OSC setup, Added periph.c/h 
					for PPS setup, Added check for USB 
					connection to UART setup, Fixed UART 
					BRG was off by one, Added override of 
					write() because the library verion will 
					automatically enable UART Tx which is 
					not desired if no USB is connected.
Eric Walker			20101113	Fixed up a lot of memory
								issues, got interupt based
					serial with circular buffers implmented,
					started console code.
Eric Walker			20101117	More clean up, rewrote serial
								port and UART configuration
					code, began simplifying the directory 
					structure, added to \n to CRLF conversion
					to write() for correct terminal behavior.
Eric Walker			20101120	Still more clean up, rewrote
								config and initialization for
					digital IO ports into gpio.c/h, began
					project wide clean up of defines and 
					header files, brought FreeRTOS up to 
					current v6.1.0 and moved it to Timer5 and
					flattened the rtos/ directory structure,
					TODO: rtcc, SD card, FATFs, nic/enc28j60,
					then look at uIP and its apps.
Eric Walker			20101121	Release alpha v0.0.0 to SVN,
								more clean up, removed more
					unneeded files from the source directory.
=============================================================

All original files for this project are available from 
http://dangerous-prototypes-open-hardware.googlecode.com/svn
under the /trunk/web-platform/firmwareA2/ directory.

This firmware is designed to run on a "Web Platform" which is
an opern hardware project developed by Dangerous Prototypes.
Please see http://dangerousprototypes.com/docs/Web_Platform
for more information.

This project is built using Microchip's MPLAB v8.xx IDE and
their C30 compiler tool suite (currently v3.23).  Please 
visit http://www.microchip.com for these tools and more 
information.

This project makes use of FreeRTOS.  Please see 
http://www.freertos.org for more information and the original 
source code.

This project makes use of  uIP.  Please see 
http://www.sics.se/~adam/uip/index.php/Main_Page for more
information and the original source code.

This project makes use of  FatFs.  Please see 
http://elm-chan.org/fsw/ff/00index_e.html for more 
information and the original source code.

Unless otherwise noted, all files in this project are 
released under the Creative Commons CC-BY-SA license.
Please see http://creativecommons.org for more information
and the full terms of this license.




=============================================================
Original 20101010 Notes below.
=============================================================

By Matt Callow Oct 2010

FreeRTOS - V6.0.5
uIP - V1.0
FatFS - R0.08a
Ethernet interface with DMA is from the uIPStack by bonyrown

Current state:
 - Pre-emptive FreeRTOS kernel
 - Ethernet using DMA
 - Fat Filesystem, accessing the micro-SD card
 - TCP/IP stack (uIP) running in a single task with:
   - Web server, serving pages from the SD card
   - dhcp client

The we server reads file from the /WWW directory on the SD card. 
Change the WWW_ROOT #define in httpd.c if you want to change this
Currently, there FAT support is for 8.3 filenames only. 
Therefore, you should create INDEX.HTM in the WW_ROOT of the SD card. This will be the default start page.

On statup, the server will request an IP address via dhcp. The configured IP address is written to the serial port.

TODO:
 - CGI scripts/SSI - actually control something via the web interface!
 - Reduce memory usage
 - work out why we can't send full size segments from httpd
 - Better handling of SD card startup
 - Code cleanup
 - DHCPC - renew lease
 - LFN support?
 - Better logging
 - Telnet?
 - Microchip IP announce protocol?

