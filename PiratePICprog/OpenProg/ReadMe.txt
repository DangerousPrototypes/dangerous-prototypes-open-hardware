OpenProg: control program for open programmer, 
an USB programmer for PIC and ATMEL micros, I2C/SPI/MicroWire memories, and other I2C/SPI devices.
Website: http://openprog.altervista.org
These sources are given free of charge under the GNU General Public License version 2 

Changelog (to use new features the corresponding firmware is required):

V 0.7.5	june 2010:		corrected write bug for 18Fx config (introduced in v.0.7.4),
						added "goto ICD" write for 16Fx,
						various minor fixes

V 0.7.4	may 2010:		added PIC24H, dsPIC30, dsPIC33, 18FxxKxx, 18FxxJxx,
						eliminated many MFC objects,
						fixed: config word verify, 24F and 18F algorithm, various

V 0.7.3	april 2010:		added 16F1xxx, some code polishing, 
						separated fileIO.cpp and made similar to command-line version

V 0.7.2	march 2010:		added some uW memories, corrected 16F7xx algo, various bugfixes

V 0.7.1	february 2010:	added support for some PIC18 and Atmel micros

V 0.7.0	january 2010:	added support for I2C EEPROMs and some PIC24F micros

V 0.6.2	october 2009:	corrected algorithms for 16F628 16F87/88 and 81X; bin file support with EE memories

V 0.6.1	september 2009:	added support for 93Cx6 EEPROMs and some Atmel micros, corrected some bugs

V 0.6.0	june 2009:  	added support for 93Sx6 MicroWire EEPROMs

V 0.5.3 march 2009: 	corrected a bug with PIC18 config words

V 0.5.2 march 2009: 	added some PIC and Atmel micros, corrected some bugs

V 0.5.1 january  2009: 	added some PIC micros, corrected some bugs

V 0.5.0	november 2008: 	added some ATMEL micros(90S8515, 90S1200), universal support for I2C/SPI

V 0.4.0	august 2008: 	added I2C memories (24XX).

V 0.3.0	july 2008:		first public release, supports PIC 10,12,16,18.
