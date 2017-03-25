
CC = cc
CFLAGS = -g -W -Wall --std=c11
LDFLAGS = -g
LDLIBS = -lpthread

EXE = httpd auth_server

all : $(EXE)

httpd : common.o tools.o auth_client.o 
auth_server :

httpd.o : 
common.o :
auth_server.o :
auth_client.o :
tools.o :

clean :
	rm -f $(EXE) *.o
