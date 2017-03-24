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

static unsigned int myport; /* my port number */

/* Handle one http request. */
void handle_request (int sock)
{
    /* XXXX A compléter */
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

    /* XXXX A compléter */
}

