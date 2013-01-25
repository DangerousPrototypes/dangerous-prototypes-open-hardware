import serial, struct

ser = serial.Serial( 'COM24', timeout=None )

frequency = 10000000 # 2 .. 10000000 (15000000 with OVERCLOCK)
duty_percent = 50

SYSCLK = 40000000
##SYSCLK = 60000000 # OVERCLOCK

PBCLK = SYSCLK / 2
if frequency > PBCLK / 2:
    assert False # SYSCLK/4 Hz is the highest frequency possible.
elif frequency > PBCLK / 65536:
    prescale_value = 1; TCKPS = 0
elif frequency > PBCLK / 2 / 65536:
    prescale_value = 2; TCKPS = 1
elif frequency > PBCLK / 4 / 65536:
    prescale_value = 4; TCKPS = 2
elif frequency > PBCLK / 8 / 65536:
    prescale_value = 8; TCKPS = 3
elif frequency > PBCLK / 16 / 65536:
    prescale_value = 16; TCKPS = 4
elif frequency > PBCLK / 32 / 65536:
    prescale_value = 32; TCKPS = 5
elif frequency > PBCLK / 64 / 65536:
    prescale_value = 64; TCKPS = 6
elif frequency > PBCLK / 256 / 65536:
    prescale_value = 256; TCKPS = 7
else:
    assert False # 2 Hz is the lowest frequency possible.

timer_clock = PBCLK / prescale_value
period = int( timer_clock / frequency )
duty_cycle = int( timer_clock / frequency * duty_percent / 100 )
print timer_clock / float( period ), 'Hz,', duty_cycle * 100 / float( period ), '%'
ser.write( 't' + struct.pack( '<H', period - 1 ) + struct.pack( '<H', duty_cycle ) )
ser.write( 'p' + struct.pack( '<B', TCKPS ) )

ser.close()
