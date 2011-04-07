/* USB Serial Transmit Bandwidth Test for Teensy USB Development Board
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2009 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include "usb_serial.h"

#define LED_CONFIG	(DDRD |= (1<<6))
#define LED_ON		(PORTD &= ~(1<<6))
#define LED_OFF		(PORTD |= (1<<6))
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

void send_str(const char *s);

#define CLEAR_TIMER0_OVERFLOW() (TIFR0 |= (1<<TOV0))
#define IS_TIMER0_OVERFLOW() (TIFR0 & (1<<TOV0))


// USB Serial Transmit Bandwidth Test
//
// Within 5 seconds of opening the port, this program
// will send a message as rapidly as possible, for 10 seconds.
// When finished, turn off text capture (some programs will not
// write the last data until you do this), delete any extra lines
// at the beginning, and then the file size divided by 10 is the
// maximum transmit bandwidth.
//
// To use this, run a terminal emulator and select the option
// to capture all text to a file.  On Linux & MacOS, you can use
// the cat command to read data to a file, such as:
// cat /dev/cu.usbmodem12341 > /tmp/test.txt
// The serial_read.exe or serial_list program can read the data
// without saving it.
// Results can vary depending on the number of other USB devices
// connected.  For fastest results, disconnect all others.

// Results on Ubuntu 9.04, using: ./serial_listen /dev/ttyACM0
// Teensy++: 11565234 in 10 seconds
// Teensy:    9610184 in 10 seconds

// Results on Mac OS X 10.5.7, using: ./serial_listen /dev/cu.usbmodem12341
// Teensy++:  9013787 in 10 seconds
// Teensy:    6386395 in 10 seconds

// Results on Windows XP SP3, using: serial_read.exe COM3:
// Teensy++: 10220367 in 10 seconds
// Teensy:    8196387 in 10 seconds

// Results on Windows Vista SP1, using: serial_read.exe COM3:
// Teensy++: 10234275 in 10 seconds
// Teensy:    8196204 in 10 seconds

// Results on Windows 7 (beta 7100), using: serial_read.exe COM3:
// Teensy++: 10274718 in 10 seconds
// Teensy:    8225423 in 10 seconds

// All 5 of these were tested on a Macbook with Intel dual core 2.4 Ghz,
// external USB mouse + built-in USB peripherals


int main(void)
{
	uint8_t n;
	uint16_t count;
	const char test_string[] = {  
		"USB Fast Serial Transmit Bandwidth Test, capture this text.\r\n"};

	// set for 16 MHz clock, and turn on the LED
	CPU_PRESCALE(0);
	LED_CONFIG;
	LED_OFF;
	DDRC |= (1<<2);  // Pin C2 to show % cpu usage

	// configure timer0 to overflow every 4 ms, prescale=256, top=250
	// 250 * 256 / 16 MHz = 4 ms
	TIMSK0 = 0;
	TCCR0A = (1<<WGM01)|(1<<WGM00);
	OCR0A = 250;
	TCCR0B = (1<<WGM02)|(1<<CS02);

	// initialize the USB, and then wait for the host
	// to set configuration.  If the Teensy is powered
	// without a PC connected to the USB port, this 
	// will wait forever.
	usb_init();
	while (!usb_configured()) /* wait */ ;
	_delay_ms(1000);

	while (1) {
		// wait for the user to run their terminal emulator program
		// which sets DTR to indicate it is ready to receive.
		while (!(usb_serial_get_control() & USB_SERIAL_DTR)) /* wait */ ;

		// Turn the LED on while sending data
		LED_ON;

		// give the user 5 seconds to enable text capture in their
		// terminal emulator, or do whatever to get ready
		for (n=5; n; n--) {
			send_str(PSTR("10 second speed test begins in "));
			usb_serial_putchar(n + '0');
			send_str(PSTR(" sec.\r\n"));
			if (!(usb_serial_get_control() & USB_SERIAL_DTR)) break;
			_delay_ms(1000);
		}

		// wait for a 4 ms timer0 period to begin
		CLEAR_TIMER0_OVERFLOW();
		while (!IS_TIMER0_OVERFLOW()) /* wait */ ;
		CLEAR_TIMER0_OVERFLOW();
		count=0;

		// send a string as fast as possible, for 10 seconds
		while (1) {
			usb_serial_write(test_string, (uint16_t)(sizeof(test_string)-1));
			if (IS_TIMER0_OVERFLOW()) {
				CLEAR_TIMER0_OVERFLOW();
				count++;
				if (count == 2500) break;   // 10 sec
				if (!(usb_serial_get_control() & USB_SERIAL_DTR)) break;
			}
		}
		PORTC &= ~(1<<2);
		send_str(PSTR("done!\r\n"));
		LED_OFF;

		// after the test, wait forever doing nothing,
		// well, at least until the terminal emulator quits
		// or drops DTR for some reason.
		while (usb_serial_get_control() & USB_SERIAL_DTR) /* wait */ ;
	}
}

// Send a string to the USB serial port.  The string must be in
// flash memory, using PSTR
//
void send_str(const char *s)
{
	char c;
	while (1) {
		c = pgm_read_byte(s++);
		if (!c) break;
		usb_serial_putchar(c);
	}
}


