CC = gcc
CFLAGS = -g -O0 -std=c99
LDFLAGS = -static

OBJS =  main.o pump.o data_file.o serial.o


all: pump-loader

pump-loader:  $(OBJS)
	$(CC) $(CFLAGS) -o pump-loader $(OBJS) $(LFD_OBJS) $(LDFLAGS)

%.o:	%.c
	$(CC) $(CFLAGS) $(DEFS) -c $<


clean:
	rm -f pump-loader *.o

