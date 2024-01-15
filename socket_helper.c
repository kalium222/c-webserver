#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include "socket_helper.h"

int open_clientfd(char *hostname, char *port) {
	int clientfd;
	struct addrinfo hints, *listp, *p;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
	int rc;
	if ((rc=getaddrinfo(hostname, port, &hints, &listp)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
		exit(1);
	}

	for (p=listp; p; p=p->ai_next) {
		if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) continue;
		if (connect(clientfd,  p->ai_addr, p->ai_addrlen) != -1) break;
		close(clientfd);
	}

	freeaddrinfo(listp);
	if (p) return clientfd;
	else return -1;
}

int open_serverfd(char *port) {
	int listenfd, optval = 1;
	struct addrinfo hints, *listp, *p;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG | AI_NUMERICSERV;
	int rc;
	if ((rc=getaddrinfo(NULL, port, &hints, &listp)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
		exit(1);
	}

	for (p=listp; p; p=p->ai_next) {
		if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) continue;
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
				(const void*)optval, sizeof(int));
		if (bind(listenfd,  p->ai_addr, p->ai_addrlen) == 0) break;
		close(listenfd);
	}

	freeaddrinfo(listp);
	if (!p) return -1;

	if (listen(listenfd, LISTENQ) < 0) {
		close(listenfd);
		return -1;
	}
	return listenfd;

}

