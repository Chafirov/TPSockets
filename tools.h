#ifndef TOOLS_H

#define HEADER200 "HTTP/1.1 200 Ok\nServer: le mien\nContent-Type: text-plain\n\n"
#define HEADER400 "HTTP/1.1 400 Not Found\nServer: le mien\nContent-Type: text-plain\n\n"


void respond400(int socket);

void respond200(int fd, int socket);

#endif
