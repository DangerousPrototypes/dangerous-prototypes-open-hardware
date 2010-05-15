Dangerous Prototypes Web Platform uip port (with DMA)

Notes about dsPIC DMA and SPI
=============================
The DMA datasheets are clear that in master mode, to receive
only, you need to either assign another DMA channel to send
null data, or use the "NULL Write" mode to send a null byte
so that the receive bytes continue to be clocked in.

What it DOESN'T say is that to send bytes only, you MUST assign
a second DMA channel to read the bytes from SPIxBUF.

If this isn't done, the SPIROV (receive buffer overflow) bit will
get set after the second byte is transmitted because nothing has read
from SPIxBUF. When SPIROV is set, ALL SPI operations on that SPI
peripheral stops.

In this case, the other DMA channel is only enabled when required,
is setup to transfer to a single memory location, and to
receive more bytes than being sent. That should prevent this DMA
channel's interrupt ever occuring (cause we don't really care
about it)


The DMA buffer 
==============
Because the send and receives from/to the buffer are occuring
while other code is running, you must be careful not to write to 
the buffer unless you acquire the lock on it.
Use the acquireBuffer() function to do that.
Typically, if uip is calling your app (either because it received
a packet, or uip is idle) the buffer would already be locked for 
your use.