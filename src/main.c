#include "model.h"
#include "socket_helper.h"
#include "tiny.h"

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int listenfd, connfd;
	char hostname[MAXLINE], port[MAXLINE];
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;

	if (argc!=2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}

	listenfd = open_serverfd(argv[1]);
	clientlen = sizeof(clientaddr);
	connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
	getnameinfo((struct sockaddr*)&clientaddr, clientlen, hostname, MAXLINE,
			port, MAXLINE, 0);
	printf("Accept connection from (%s, %s)\n", hostname, port);

	doit(connfd);
	close(connfd);

	return 0;
}

