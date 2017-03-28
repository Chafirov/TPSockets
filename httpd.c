/*
 * Un serveur httpd basique
 * Time-stamp: <26 mar 2015 10:47 queinnec@enseeiht.fr>
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <err.h>
#include "common.h"
#include "auth.h"

#include "tools.h"

#define N7

#ifndef N7
#define PATH_TO_FILE           "/home/raskolnikov/dev/sockets/"
#else
#define PATH_TO_FILE           "/home/gjolly/2TR/sockets/"
#endif

static unsigned int myport; /* my port number */


/* Handle one http request. */
void handle_request (int sock)
{
	printf("Socket ouvert\n");
	char* requestLine = read_request(sock);
	printf("Line read\n");
	int method;
	char* filename;
	
	parse_request(requestLine, &method, &filename);

    printf("Requète parsée\n");

    char fullFileName[100] = PATH_TO_FILE;
    strcat(fullFileName, filename);

    printf("Nom du fichier à trouver : %s\n", fullFileName);

	if(method != 1){
		respond400(sock);
	} else {
		int file = open(fullFileName, O_RDONLY);
		if (file == -1){
			printf("Pas de ficher\n");
			respond400(sock);
		} else {
			printf("Fichier ouvert\n");
			respond200(file, sock);
		}
	}
	close(sock);
}


int main (int argc, char *argv[])
{
    struct sockaddr_in soc_in;
    int s, r, val;
    int authport;

    if (argc != 3) {
        fprintf(stderr, "%s <port> <authport>\n", argv[0]);
        exit(2);
    }

    myport = atoi(argv[1]);
    authport = atoi(argv[2]);

    auth_init(authport);

    signal(SIGPIPE, SIG_IGN);

    /* socket Internet, de type stream (fiable, bi-directionnel) */
    s = socket (AF_INET, SOCK_STREAM, 0);
    if (s == -1) err(1, "socket");

    /* Force la réutilisation de l'adresse si non allouée.
     * (cela permet de relancer le serveur immédiatement après une
     * "sale" terminaison, i.e. sans fermeture propre (close ou shutdown)
     * du socket d'écoute). */
    val = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val)) == -1)
      err (1, "setsockopt");

    /* Nomme le socket: socket inet, port myport, adresse IP quelconque */
    soc_in.sin_family = AF_INET;
    soc_in.sin_addr.s_addr = INADDR_ANY;
    soc_in.sin_port = htons(myport);
    r = bind (s, (struct sockaddr *)&soc_in, sizeof(soc_in));
    if (r == -1) err(1, "bind");

    /* Prépare le socket à la réception de connexions */
    listen (s, 5);

	while(1){

		struct sockaddr peer;
		socklen_t addrlen = sizeof(struct sockaddr_in);
		int newSock = accept(s, &peer, &addrlen);
		if (newSock != -1){
			pthread_t thread;
			pthread_create(&thread, NULL, &handle_request, newSock);
		} else 
			perror("Socket = -1");
		
	}
}

