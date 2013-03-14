#!/usr/bin/env python
# encoding: utf-8
"""
Created by Sean Nelson on 2009-10-14.
Copyright 2009 Sean Nelson <audiohacked@gmail.com>

This file is part of pyBusPirate.

pyBusPirate is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pyBusPirate is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pyBusPirate.  If not, see <http://www.gnu.org/licenses/>.
"""

import select
import serial
import sys
import time

"""
PICSPEED = 24MHZ / 16MIPS
"""


class PinCfg:
	POWER = 0x8
	PULLUPS = 0x4
	AUX = 0x2
	CS = 0x1


class BBIOPins:
	# Bits are assigned as such:
	MOSI = 0x01
	CLK = 0x02
	MISO = 0x04
	CS = 0x08
	AUX = 0x10
	PULLUP = 0x20
	POWER = 0x40


class BBIO:
	def __init__(self, p="/dev/bus_pirate", s=115200, t=1):
		self.port = serial.Serial(p, s, timeout=t)

	def BBmode(self):
		if sys.platform == 'win32':
			# I haven't seen this problem on Windows, which is good,
			# because it doesn't appear to support select.select()
			# for serial ports.  This seems to work instead:
			self.resetBP()
			self.port.write("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")
			self.timeout(0.1)
			self.port.flushInput()
			self.reset()
		else:
			# Sometimes sending 20 zeroes in a row to a BP already in binary mode
			# leads to BP getting stuck in BitBang mode
			# (see forum: http://dangerousprototypes.com/forum/viewtopic.php?t=1440#msg13179 )
			# so if we detect a response (indicating we're in BitBang mode before the 20 zeroes)
			# stop sending zeroes and go on.
			self.port.flushInput()
			for i in range(20):
				self.port.write("\x00")
				r, w, e = select.select([self.port], [], [], 0.01)
				if (r):
					break

		if self.response(5) == "BBIO1":
			return 1
		else:
			return 0

	def reset(self):
		self.port.write("\x00")
		time.sleep(0.1)

	def enter_SPI(self):
		self.response(5, errOnTimout=False)
		self.port.write("\x01")

		if self.response(4) == "SPI1":
			return 1
		else:
			return 0

	def enter_I2C(self):
		self.port.write("\x02")

		if self.response(4) == "I2C1":
			return 1
		else:
			return 0

	def enter_UART(self):
		self.port.write("\x03")

		if self.response(4) == "ART1":
			return 1
		else:
			return 0

	def enter_1wire(self):
		self.port.write("\x04")

		if self.response(4) == "1W01":
			return 1
		else:
			return 0

	def enter_rawwire(self):
		self.port.write("\x05")

		if self.response(4) == "RAW1":
			return 1
		else:
			return 0

	def resetBP(self):
		self.reset()
		self.port.write("\x0F")

		#self.port.read(2000)
		self.port.flushInput()
		return 1

	def raw_cfg_pins(self, config):
		self.port.write(chr(0x40 | config))

		return self.response(1)

	def raw_set_pins(self, pins):
		self.port.write(chr(0x80 | pins))

		return self.response(1)


	def response(self, byte_count=1, return_data=False, timeout=0.1, errOnTimout=True):		# This is basically the primary communication function.
													# The timeout function is new, and the other tools (aside from the SPI library, which has been tested pretty thoroughly)
													# will need to be tested

													# Adding the ability to receive an unknown number of bytes would be a very good idea in the near future

		startTime = time.time()

		while (self.port.inWaiting() < byte_count) and (time.time() < (startTime + timeout)):		# Wait until we have the desired number of
			time.sleep(0.001)									# bytes in the receive buffer

		if time.time() > (startTime + timeout) and errOnTimout:
			raise IOError("Response Timed out")

		data = self.port.read(byte_count)

		if byte_count == 1 and return_data is False:				# If you don't request anyt return data, the bus-pirate returns 0x01 upon success
			if data == chr(0x01):
				return 1
			else:
				return 0
		else:
			return data

	""" Self-Test """
	def short_selftest(self):
		self.port.write("\x10")

		return self.response(1, True)

	def long_selftest(self):
		self.port.write("\x11")

		return self.response(1, True)

	""" PWM """
	def setup_PWM(self, prescaler, dutycycle, period):
		self.port.write("\x12")
		self.port.write(chr(prescaler))
		self.port.write(chr((dutycycle >> 8) & 0xFF))
		self.port.write(chr(dutycycle & 0xFF))
		self.port.write(chr((period >> 8) & 0xFF))
		self.port.write(chr(period & 0xFF))

		return self.response()

	# Sets the pwm frequency in 1khz multiples as the BusPirate shell/firmware does
	def set_1khz_pwm_frequency(self, kilohertz, duty_cycle = .5):
		if kilohertz < 4:
			pwm_div = 62
			prescaler = 3

		elif kilohertz < 31:
			pwm_div = 250
			prescaler = 2
		elif kilohertz < 245:
			pwm_div = 2000
			prescaler = 1
		else:
			pwm_div = 16000
			prescaler = 0

		period = (pwm_div / kilohertz) - 1

		duty = int(period * duty_cycle)

		#print "prescaler ", prescaler, "duty ", duty, "period ", period

		return self.setup_PWM(prescaler, duty, period)

	# Sets the pwm aux pin at an specific frequency and duty cycle
	#
	# The code follows the PIC24FJ64 datasheet specification an the
	# PIC24F family reference manual.
	#
	# Basically it finds the highest period register value for the timer
	# based on our target frequency or target period.
	#
	# The timer input clock is rated at Fosc/2 and it's called on the
	# datasheets as Tcy, the BusPirate uses the internal 8Mhz clock with
	# the PLL module enabled, so finally it uses a 32Mhz clock, Tcy
	# is 16Mhz or a 62.5ns period.

	def set_pwm_frequency(self, frequency, duty_cycle = 0.5):

		prescalers = [1.0, 1.0 / 8, 1.0 / 64, 1.0 / 256]

		# Timer input frequency = Fosc/2 --> 16000000Hz
		# Timer period with 1:1 prescaler = 1/16000000 --> 0.0000000625s --> 0.0625us --> 62.5ns

		tcy = 0.0000000625

		target_period = 1.0 / frequency

		# precalc some part of the period register formula
		dummy = target_period / tcy

		prescaler = -1

		for I in range(4):
			period = dummy * prescalers[I] - 1

			# It's a valid 16 bits period register value?
			if period < 65536:
				# If so we have found the greatest one
				prescaler = I
				break

		# If we have found a valid prescaler, calc the duty cycle value
		# and call the BusPirate function for stablishing the PWM configuration

		if prescaler != -1:
			duty = int(period * duty_cycle)
			#print "prescaler ", prescaler, " period ", period, "duty", duty
			return self.setup_PWM(prescaler, duty, int(period))
		else:
			print "Can't setup ", frequency, "Hz."


	def clear_PWM(self):
		self.port.write("\x13")

		return self.response()

	""" ADC """
	def ADC_measure(self):
		self.port.write("\x14")

		return self.response(2, True)

	""" General Commands for Higher-Level Modes """
	def mode_string(self):
		self.port.write("\x01")

		return self.response()

	def bulk_trans(self, input):
		if type(input) == int:
			byteList = [0] * input
			byteCount = input
		elif type(input) == list:
			byteList = input
			byteCount = len(input)
		else:
			raise ValueError("Invalid data type")


		self.port.write(chr(0x10 | (byteCount - 1)))

		for i in range(byteCount):
			self.port.write(chr(byteList[i]))

		data = self.response(byteCount + 1, True)
		return data[1:]

	def cfg_pins(self, pins=0):
		self.port.write(chr(0x40 | pins))

		return self.response()

	def read_pins(self):
		self.port.write("\x50")

		return self.response(1, True)

	def set_speed(self, spi_speed=0):
		self.port.write(chr(0x60 | spi_speed))

		return self.response()

	def read_speed(self):
		self.port.write("\x70")

		return self.response(1, True)

