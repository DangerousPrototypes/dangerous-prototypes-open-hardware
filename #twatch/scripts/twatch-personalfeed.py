#!/usr/bin/python
#By: twonk (http://whereisian.com/forum/index.php?topic=145.msg823#msg823)
#Hello all,  Here's a python script I run on a linux box that pushes my twitter feed to my #twatch.
#The code is based off WA5ZNU's orignal script to turn the backlight on and off.  His code is great,
#mine more than likely has many errors/inconsistencies/duplication/bad practices.  It's my first attempt at Python, 
#so if anyone cares to tidy up or improve the code then please go ahead.
#
#Save the code as twatch.py
#
#Basic usage is:     twatch.py twitter   
#which will start scrolling your friend timeline on lcd line 1,  
#Mentions on line 2, DMs on line 3 and some of the public timeline on line 4.
#
#Be sure to set your #twatch IP address and twitter username and password in the script.
#
#Many thanks to WA5ZNU who originally wrote the basis of this script
#to turn the twatch backlight on and off.

import socket, struct
import sys, time
import simplejson, urllib
from threading import Thread

#Connect to the #twatch TCP server at the IP address shown on the LCD screen.
#Send the command 0xFE 0x42 0x00 to turn on the backlight.
#Send the command 0xFE 0x46 to turn it off.
HOST="192.168.0.37"
PORT=1337

#Twitter login details
TWITTER_USER = ''
TWITTER_PASS = ''

#twitter basic URLs
TWITTER_URL_FRIEND = 'https://' + TWITTER_USER + ':' + TWITTER_PASS + '@twitter.com/statuses/friends_timeline.json'
TWITTER_URL_MENTIONS = 'https://' + TWITTER_USER + ':' + TWITTER_PASS + '@twitter.com/statuses/mentions.json'
TWITTER_URL_DMS = 'https://' + TWITTER_USER + ':' + TWITTER_PASS + '@twitter.com/direct_messages.json'
TWITTER_URL_PUBLIC = 'https://twitter.com/statuses/public_timeline.json'

#Command strings for the LCD
ONCMD = chr(0xFE) + chr(0x42) + chr(0x00)   #backlight on
OFFCMD = chr(0xFE) + chr(0x46)              #backlight off
#establish matrixmode and clear the screen
MATRIXMODE  = chr(0xFE) + chr(0x47) + chr (0x01) + chr (0x01) + chr(0xFE) + chr(0x58)
HOME   = chr(0XFE) + chr(0x48)              #position cursor at home
#return to standard functionality
RESTART =  chr(0xFE) + chr(0x9A) + chr(0xFE) + chr(0x58) + chr(0xFE) + chr(0x48)

BLANK = '                    '
msg1 = ''
msg2 = ''
msg3 = ''
msg4 = ''
since_friend = 0
since_mentions = 0
since_dm = 0
since_public = 0

def connect():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_TCP, socket.TCP_NODELAY, 1)
    sock.settimeout(10)
    sock.connect((HOST, PORT))
    return sock

def sendcmd(msg):
    sock.sendall(msg)

def scroll():
    global msg1,msg2,msg3,msg4
    while 1==1:
       if len(msg1) > 1 or len(msg2) > 1 or len(msg3) > 1 or len(msg4) > 1:
      msg = msg1.ljust(20,' ')[0:20] + msg2.ljust(20,' ')[0:20] + msg3.ljust(20,' ')[0:20] + msg4.ljust(20,' ')[0:20]
      sendcmd(HOME)
      sock.sendall(msg)
      checkflash()
      msg1 = msg1[1:]
      msg2 = msg2[1:]
      msg3 = msg3[1:]
      msg4 = msg4[1:]
            #scrolling can be slowed down here if required
       #time.sleep(0.4)

#Flash the backlight when we recieve a DM or Mention
def checkflash():
    if msg2.find(TWITTER_USER)<=10 and msg2.find(TWITTER_USER)>=0 :
   flash(msg2)
    elif msg3.find(TWITTER_USER)<=10 and msg3.find(TWITTER_USER)>=0 :
   flash(msg3)

def flash(msg):
    if msg.find(TWITTER_USER)%2 == 0 :
   sendcmd(ONCMD)
    else:
   sendcmd(OFFCMD)

def twit(url, msg):
    global since_friend, since_mentions, since_dm, since_public
    since = 0
    if url == TWITTER_URL_FRIEND:
        since = since_friend
    elif url == TWITTER_URL_MENTIONS:
        since = since_mentions
    elif url == TWITTER_URL_DMS:
        since = since_dm
    else:
        since = since_public
    if since > 0:
        turl = url + '?since_id=' + str(since)
    else:
        turl = url + '?count=2'
    results = simplejson.load(urllib.urlopen(turl))
    if 'error' in results:
        msg = msg.rstrip()  +'***Error*** ' + results['error'].encode("utf-8")
    else:
        for result in results:
            if result['id'] > since:
                since = result['id']
                if url == TWITTER_URL_FRIEND:
                    since_friend = result['id']
                elif url == TWITTER_URL_MENTIONS:
                    since_mentions = result['id']
                elif url == TWITTER_URL_DMS:
                    since_dm = result['id']
                else:
                    since_public = result['id']
            if len(msg) > 20:
                msg = msg.rstrip()
            else:
                msg = BLANK + msg
            if url == TWITTER_URL_DMS:
                msg = msg + ' Sender:' + result['sender']['name'].encode("utf-8") + ':@' + result['recipient']['screen_name'].encode("utf-8") + ' ' + result['text'].encode("utf-8")+ BLANK   
            else:
                msg = msg + ' User:' + result['user']['name'].encode("utf-8") + ':' + result['text'].encode("utf-8") + BLANK
    return msg



#Thread to deal with twitter friend timeline
def twitter():
    while 1==1:
       global msg1
       msg1 = twit(TWITTER_URL_FRIEND, msg1)
       time.sleep(60)  #Look for new messages every minute

#Thread to deal with twitter mentions
def twitter_mentions():
    while 1==1:
       global msg2
       msg2 = twit(TWITTER_URL_MENTIONS, msg2)
            time.sleep(300) #look for new mentions every 5 minutes

#thread to deal with twitter DMs
def twitter_dm():
    while 1==1:
        global msg3
        msg3 = twit(TWITTER_URL_DMS, msg3)
        time.sleep(600) #Check DMs every 10 minutes


#Thread for loading the public timeline
def twitter_public():
    global msg4
    while 1==1:
        #Only load new messages if we're got less than 200 characters to scroll.
        #stops overloading
        if len(msg4)<200:
       msg4 = twit(TWITTER_URL_PUBLIC, msg4)
        time.sleep(60)  #Sleeps for 1 minutes


def command(cmd, switch):
    if cmd == 'backlight':
        if switch == 'off' :
            sendcmd(OFFCMD)
        else:
            sendcmd(ONCMD) 
    elif cmd == 'restart':
        sendcmd(RESTART)
    elif cmd == 'matrix':
        sendcmd(MATRIXMODE)
    elif cmd == 'scroll':
        switch = BLANK + switch + BLANK
        scroll(switch)
    elif cmd == 'twitter':
   sendcmd(ONCMD)
   sendcmd(MATRIXMODE)
   Thread(target=twitter).start()
   Thread(target=twitter_mentions).start()
   Thread(target=twitter_dm).start()
   Thread(target=twitter_public).start()
   Thread(target=scroll).start()
   
if len(sys.argv) > 1:
    sock = connect()
    cmd = sys.argv[1]
    switch = ''
    if len(sys.argv) > 2:
        switch = sys.argv[2]
    command(cmd, switch)
   

time.sleep(0.1)                 # wait for socket library
