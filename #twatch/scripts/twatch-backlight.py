#!/usr/bin/python
#By: WA5ZNU (http://wa5znu.org/2009/11/twatch/)
import socket, struct
import sys, time

HOST="twatch.graflex.org"
PORT=1337

#Connect to the #twatch TCP server at the IP address shown on the LCD screen.
#Send the command 0xFE 0x42 0x00 to turn on the backlight. 
#Send the command 0xFE 0x46 to turn it off.

ONCMD = chr(0xFE) + chr(0x42) + chr(0x00)
OFFCMD = chr(0xFE) + chr(0x46)

def connect():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_TCP, socket.TCP_NODELAY, 1)
    sock.settimeout(10)
    sock.connect((HOST, PORT))
    return sock

def sendcmd(msg):
    sock.sendall(msg)

def backlight(cmd):
    if cmd == 'off':
        sendcmd(OFFCMD)
    else:
         sendcmd(ONCMD)

if len(sys.argv) > 1:
    sock = connect()
    backlight(sys.argv[1])
else:
    print("usage: twatch off|on")

time.sleep(0.1)                 # wait for socket library
