EXE=picprog
CC = gcc
CFLAGS = -g -O0 -std=gnu99
LDFLAGS =

OBJS = data_file.o common.o
OBJS += pic.o proto_pic.o pic12.o pic16.o pic18.o pic24.o
OBJS += iface.o buspirate.o serial.o

all: $(EXE)

$(EXE):  $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(LFD_OBJS) $(LDFLAGS)

%.o:	%.c
	$(CC) $(CFLAGS) $(DEFS) -c $<

clean:
	rm -f $(EXE) *.o

