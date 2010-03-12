# Makefile for DOSFS demo applet
# Lewin A.R.W. Edwards (sysadm@zws.com)
# 2005-12-31
OPTS    = -DHOSTVER
EXE     =  dosfs
SOURCES =	main.c \
			dosfs.c \
			hostemu.c \
			$(eolist)
OBJS    = ${SOURCES:.c=.o}
CFLAGS  =
LDADD   = 
CC      = gcc

all : ${EXE}

${EXE} : ${OBJS}
	${CC} -o ${EXE} ${OBJS} ${LDADD}
	chmod 755 ${EXE}

.c.o:
	${CC} ${CFLAGS} ${OPTS} -c $<

clean:
	rm -f *.o
	rm -f ${EXE}
	rm -f *~
