#!/usr/bin/python
# http://dangerousprototypes.com/forum/index.php?topic=380
#
# twServer.py - python code to drive the Twatch.
#
# right now, just displays date time + weather report
#
#
# Note: need to enter "matrix" mode to turn off the tweetering stuff
# And the partial backlight thing doesn't seem to work...
#
# Many thanks to WA5ZNU and twonk who originally wrote the python scripts talking to
# the twatch. And Ian and DangerousPrototypes for making the twatch.
#
# This was written with Active-State Python, and requires the pywapi python weather
# module, which you can get from http://code.google.com/p/python-weather-api/.
# So you'll need to put pywapi.py in the same directory as this file, and you'll see
# weather reports on your twatch.
#
# This program takes a command line argument to figure out what to do. Check out the
# command() routine to see how that works. The most useful ones are:
#   twServer.py   matrix        - tells the twatch to stop Twittering and process MatrixOrbital commands
#   twServer.py   display "Hi, I'll be displayed on the twatch"
#   twServer.py   server        - enter an infinite loop, displaying time, and weather info
#   twServer.py   twitter       - go back to twittering mode
# 
# I tried to get code working that set the customcharacter set working, so I could
# display large digit times. But it didn't seem to work. So I just display the time
# with ascii characters like | + and -.
#
# Finally, if you don't live in NYC you probably want to put your own zip code into
# the call to google weather (pywapi.get_weather_from_google('10025'))
# there is also code to fetch current weather from yahoo, which uses FAA designations,
# but I found it much easier to deal with the forecasts from google.
#
# thanks for all the folks who've done things to make this project possible, it's a lot
# of fun.  trobbinsmilne

import socket, struct
import sys
import pywapi
import string
import time


#Connect to the #twatch TCP server at the IP address shown on the LCD screen.
HOST="192.168.1.104"
PORT=1337

#Command strings for the LCD
ONCMD = chr(0xFE) + chr(0x42) + chr(0x00)   #backlight on
OFFCMD = chr(0xFE) + chr(0x46)              #backlight off
CONTRAST = chr(0xFE) + chr(80)              # follow with byte of "contrast" 0..FF, FF has "on" darkest
#establish matrixmode and clear the screen
MATRIXMODE  = chr(0xFE) + chr(0x47) + chr (0x01) + chr (0x01) + chr(0xFE) + chr(0x58)
HOME   = chr(0XFE) + chr(0x48)              #position cursor at home
#return to standard functionality
RESTART =  chr(0xFE) + chr(0x9A) + chr(0xFE) + chr(0x58) + chr(0xFE) + chr(0x48)
CLEARLCD = chr(0xFE) + chr(0x58)
CURSORON = chr(0xFE) + chr(0x53)
CURSOROFF = chr(0xFE) + chr(0x54)
UNDERLINEON = chr(0xFE) + chr(0x48)
UNDERLINEOFF = chr(0xFE) + chr(0x49)
LARGEDIGITS = chr(0xFE) + chr(110)


BLANK = '                    '
msg1 = ''
msg2 = ''
msg3 = ''
msg4 = ''


def connect():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_TCP, socket.TCP_NODELAY, 1)
    sock.settimeout(10)
    sock.connect((HOST, PORT))
    return sock


def sendcmd(msg):
    sock.sendall(msg)


def clearLCD():
    sendcmd(CLEARLCD)


def backlight(nBrightness):
    sendcmd(chr(0xfe) + chr(80) + chr(nBrightness))

    
def display(msg,row,col):
    ### Note: row == 1..4, col ==1..20 """
    sendcmd(HOME)
    sock.sendall(chr(0xFE) + chr(0x47) + chr(col) + chr(row))
    sock.sendall(msg)


def largeDigit(col,digit):
    """ col == 1..18  (each takes up 3 regular columns)
        digit == 0..9 (digit to display)
    """
    sendcmd(LARGEDIGITS)
    sendcmd(chr(0xFE) + chr(35) + chr(col) + chr(digit))


def testDigits(msg):
    ### Note: row == 1..4, col ==1..20 """
    largeDigit( 1,1)
    largeDigit( 4,2)
    largeDigit( 7,3)
    largeDigit(11,4)
    largeDigit(14,5)
    largeDigit(17,6)


def defineCustomCharacter(code,b1,b2,b3,b4,b5,b6,b7,b8):
    sendcmd(chr(0xFE) + chr(78) + chr(code) + chr(b1)+chr(b2)+chr(b3)+chr(b4)+chr(b5)+chr(b6)+chr(b7)+chr(b8))
    time.sleep(.1)

    
def defineCustomFont():
    defineCustomCharacter(0,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07)
    defineCustomCharacter(1,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07)
    defineCustomCharacter(2,0x41,0x43,0x47,0x4e,0x4e,0x47,0x43,0x41)
    defineCustomCharacter(3,0x01,0x03,0x07,0x0e,0x0e,0x07,0x03,0x01)
    defineCustomCharacter(4,0x01,0x03,0x07,0x0e,0x0e,0x07,0x03,0x00)
    defineCustomCharacter(5,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x00)


def testFonts(msg):
    clearLCD()
    defineCustomFont()
    msg = ""
    for i in range(0,40):
        msg = msg + chr(i)
    msg = msg + "0123456789"
    msg = msg + "0123456789"    
    sendcmd(msg)
    

def print4Digits(number):
    """ prints a four digit number passed as a string. Assumed to be a time,
        so starting digit is either a space or a one...
    """
    msg1 = "   "
    msg2 = "   "
    msg3 = "   "
    msg4 = "   "
    if (number[0]=="1"):
        msg1 = "/| "
        msg2 = " | "
        msg3 = " | "
        msg4 = "-+-"

    for i in range(1,4):
        digit = number[i]
        if digit=="0":
            msg1 = msg1 + "+---+"
            msg2 = msg2 + "|   |"
            msg3 = msg3 + "|   |"
            msg4 = msg4 + "+---+"
        if digit=="1":
            msg1 = msg1 + " /|  "
            msg2 = msg2 + "  |  "
            msg3 = msg3 + "  |  "
            msg4 = msg4 + " -+- "
        if digit=="2":
            msg1 = msg1 + "/---+"
            msg2 = msg2 + " ___|"
            msg3 = msg3 + "|    "
            msg4 = msg4 + "+----"
        if digit=="3":
            msg1 = msg1 + "----+"
            msg2 = msg2 + " ___|"
            msg3 = msg3 + "    |"
            msg4 = msg4 + "----+"
        if digit=="4": 
            msg1 = msg1 + "|   |"
            msg2 = msg2 + "|___|"
            msg3 = msg3 + "    |"
            msg4 = msg4 + "    |"
        if digit=="5":
            msg1 = msg1 + "+----"
            msg2 = msg2 + "|___ "
            msg3 = msg3 + "    |"
            msg4 = msg4 + "____/"
        if digit=="6":
            msg1 = msg1 + "+--- "
            msg2 = msg2 + "|___ "
            msg3 = msg3 + "|   |"
            msg4 = msg4 + "+---/"
        if digit=="7":
            msg1 = msg1 + "---- "
            msg2 = msg2 + "   / "
            msg3 = msg3 + "  /  "
            msg4 = msg4 + " /   "
        if digit=="8":
            msg1 = msg1 + "+---+"
            msg2 = msg2 + "|___|"
            msg3 = msg3 + "|   |"
            msg4 = msg4 + "+---+"
        if digit=="9":
            msg1 = msg1 + "+---+"
            msg2 = msg2 + "|___|"
            msg3 = msg3 + "    |"
            msg4 = msg4 + "    |"
        if i==1 or i==2:
            msg1 = msg1 + " "
            msg2 = msg2 + " "
            msg3 = msg3 + " "
            msg4 = msg4 + " "
    display(msg1 + msg2 + msg3 + msg4,1,1)
            

def test(msg):
    print "12345678901234567890"
    print4Digits(" 230")
    print4Digits("1456")
    print4Digits("1789")
    
    
def scroll():
    global msg1,msg2,msg3,msg4
    while 1==1:
        if len(msg1) > 1 or len(msg2) > 1 or len(msg3) > 1 or len(msg4) > 1:
            msg = msg1.ljust(20,' ')[0:20] + msg2.ljust(20,' ')[0:20] + msg3.ljust(20,' ')[0:20] + msg4.ljust(20,' ')[0:20]
        sendcmd(HOME)
        sock.sendall(msg)
        print msg
        msg1 = msg1[1:]
        msg2 = msg2[1:]
        msg3 = msg3[1:]
        msg4 = msg4[1:]
        #scrolling can be slowed down here if required
        time.sleep(0.4)


def timeDisplay():
    timeLine = time.strftime("%I%M")
    print "Time: %s  %s" % (timeLine,time.strftime("%I:%M:%S %p"))
    print4Digits(timeLine)


def timeServer():
    while 1==1:
        timePrint()
        time.sleep(.3)



g_noaa_result = {}
g_noaa_cnt = 0

def fetchWeatherNoaa():
    """ every 300 calls check the weather """
    global g_noaa_result
    global g_noaa_cnt

    if g_noaa_cnt==0:
        try:
            tmp = pywapi.get_weather_from_noaa('KNYC')
            print "NOAA read: %s" % tmp
            g_noaa_result = tmp
        except:
            pass 
    g_noaa_cnt = (g_noaa_cnt+1) % 300   


g_google_result = {}
g_google_cnt = 0

def fetchWeatherGoogle():
    """ every 300 calls check the weather """
    global g_google_result
    global g_google_cnt

    if g_google_cnt==0:
        try:
            tmp = pywapi.get_weather_from_google('10025')
            print "Google read: %s" % tmp
            g_google_result = tmp
        except:
            pass 
    g_google_cnt = (g_google_cnt+1) % 300   


def weatherDisplayNoaa():
    # format of report:
    # line1: day + date
    # line2: time
    # line3: sun/cloudy/rainy + temp
    # line4: wind and wind chill

    global g_noaa_result
    fetchWeatherNoaa()
    
    cnt = 0
    whenNoaa = "NOAA"
    timeLine2 = "Startup"

    timeLine1 = time.strftime("%A %B %d")
    timeLine2 = time.strftime("%I:%M:%S %p")
    if timeLine2[0]=="0":  timeLine2 = " "+timeLine2[1:]
    timeLine1 = timeLine1.ljust(20," ")
    timeLine2 = timeLine2.ljust(20," ")
        
    outlook = g_noaa_result['weather']
    curTemp = g_noaa_result['temp_f'] + "F"
    windMph = "Wind " + g_noaa_result['wind_mph'] + "mph"
    # windDesc = g_noaa_result['windchill_f'] + ".0F"
    windDesc = g_noaa_result['wind_string']
    weather1 = outlook.ljust(14," ")[0:14] + curTemp.rjust(6," ")[0:6]
    weather2 = windMph.ljust(14," ")[0:14] + windDesc.rjust(6," ")[0:6]
    print timeLine1
    print timeLine2
    print weather1
    print weather2
    print "12345678901234567890"
    report = timeLine1[0:20]+timeLine2[0:20]+weather1[0:20]+weather2[0:20]
    display(report,1,1)


def weatherDisplayGoogle():
    # format of report:
    # line1: day + date
    # line2: time
    # line3: sun/cloudy/rainy + temp
    # line4: wind and wind chill

    global g_google_cnt
    global g_google_result
    fetchWeatherGoogle()
    

    if  g_google_cnt % 2 == 1:       
        timeLine1 = time.strftime("%A %B %d")
        timeLine2 = time.strftime("%I:%M:%S %p")
        if timeLine2[0]=="0":  timeLine2 = " "+timeLine2[1:]
        timeLine1 = timeLine1.ljust(20," ")
        timeLine2 = timeLine2.ljust(20," ")
        current = g_google_result['current_conditions']
        outlook = current['condition']
        curTemp = current['temp_f'] + "F"
        windDesc = current['wind_condition'] 
        humidity = current['humidity']
        weather1 = outlook.ljust(14," ")[0:14] + curTemp.rjust(6," ")[0:6]
        weather2 = windDesc.ljust(20," ")[0:20] 
        report = timeLine1[0:20]+timeLine2[0:20]+weather1[0:20]+weather2[0:20]
    else:
        report = ""
        forecasts = g_google_result['forecasts']
        for forecast in forecasts:
            dow = forecast['day_of_week']
            tempLo = forecast['low']
            tempHi = forecast['high']
            outlook = forecast['condition']
            fLine = ("%3s %sF %sF %s          " % (dow,tempHi,tempLo,outlook))[0:20]
            report = report + fLine
    display(report,1,1)
    print report


def weather():
    sendcmd(MATRIXMODE)
    while 1==1:
        weatherDisplayGoogle()
        time.sleep(15)

        
def server():
    sendcmd(MATRIXMODE)
    while 1==1:
        for i in range(1,4):
            timeDisplay()
            time.sleep(7)
        weatherDisplayGoogle()
        time.sleep(7)

        
def command(cmd, switch):
    if cmd == 'backlight':
        if switch == 'off' :
            sendcmd(OFFCMD)
        elif switch == 'on':
            sendcmd(ONCMD)  
        else:
            backlight(int(switch))
    elif cmd == 'restart':
        sendcmd(RESTART)
    elif cmd == 'matrix':
        sendcmd(MATRIXMODE)
    elif cmd == 'clear':
        clearLCD()
    elif cmd == 'display':
        display(switch,2,1)
    elif cmd == 'server':
        server()
    elif cmd == 'test':
        test(switch)        
    elif cmd == 'time':
        timeServer()
    elif cmd == 'scroll':
        global msg1
        global msg2
        global msg3
        global msg4
        
        msg1 = msg2
        msg2 = msg3
        msg3 = msg4
        msg4 = BLANK + switch + BLANK
        scroll()
    elif cmd == 'weather':
        weather()
    elif cmd == 'twitter':
        sendcmd(ONCMD)
    else:
        print "Unknown command, try weather"
        

    
if len(sys.argv) > 1:
    sock = connect()
    cmd = sys.argv[1]
    switch = ''
    if len(sys.argv) > 2:
        switch = sys.argv[2]
    command(cmd, switch)    

time.sleep(0.3)                 # wait for socket library
