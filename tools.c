#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"

#define HEADER200 "HTTP/1.1 200 Ok\nServer: le mien\nContent-Type: text-plain\n\n"
#define HEADER400 "HTTP/1.1 400 Not Found\nServer: le mien\nContent-Type: text-plain\n\n"

#define BUFF_SIZE 200

void respond200(int file, int socket){
	char buff[BUFF_SIZE];
	writef(socket, HEADER200);
	while(read(file, buff, BUFF_SIZE) != 0){
		printf("%s", buff);
		writef(socket, buff);
	}
}

void respond400(int socket){
	writef(socket, HEADER400);
	writef(socket, "File not found");
}
