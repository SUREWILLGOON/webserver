CC=gcc
CFLAGS=-std=c99
LIBS = -lpthread 
sureserver:main.o initDaemon.o common.o getconfig.o wrap.o connect.o respone.o parseHeader.o log.o
	$(CC) -o  sureserver main.o initDaemon.o common.o getconfig.o wrap.o  connect.o log.o respone.o parseHeader.o $(LIBS)
main.o:main.c init/initDaemon.h common/common.h log/log.h
	$(CC) -c main.c 
initDaemon.o:init/initDaemon.c getconfig/getconfig.h wrap/wrap.h
	$(CC) -c init/initDaemon.c
common.o:common/common.c 
	$(CC) -c common/common.c
getconfig.o:getconfig/getconfig.c servertypes.h common/common.h
	$(CC) -c getconfig/getconfig.c
wrap.o:wrap/wrap.c servertypes.h common/common.h
	$(CC) -c wrap/wrap.c
connect.o:connect/connect.c common/common.h wrap/wrap.h
	$(CC) -c connect/connect.c

respone.o:respone/respone.c wrap/wrap.h servertypes.h common/common.h
	$(CC) -c respone/respone.c
parseHeader.o:parse/parseHeader.c servertypes.h  common/common.h getconfig/getconfig.h
	$(CC) -c parse/parseHeader.c
log.o:log/log.c common/common.h wrap/wrap.h parse/parseHeader.h servertypes.h
	$(CC) -c log/log.c
clean:
	rm *.o

