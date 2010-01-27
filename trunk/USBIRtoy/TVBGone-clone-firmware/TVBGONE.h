/*
This is a simple player for TVBGONE power codes.
Our player is simple because PIC C18 has easy 
reads from program memory. 

This code was written based on the description 
of the data packing method published on the Adafruit 
website. It should be a clean, black-box rewrite, but 
we'll release it as CC 2.5 Attrib & Share Alike 
out of respect for the original authors.

PIC C18 Player (c) Ian Lesnet 2009
for use with IR Toy v1.0 hardware.
http://dangerousprototypes.com

With credits to:

TV-B-Gone Firmware version 1.2
for use with ATtiny85v and v1.2 hardware
(c) Mitch Altman + Limor Fried 2009
Last edits, August 16 2009

With some code from:
Kevin Timmerman & Damien Good 7-Dec-07

Distributed under Creative Commons 2.5 -- Attib & Share Alike

Ported to PIC (18F2550) by Ian Lesnet 2009
*/
void tvbgonePlayer(void);
