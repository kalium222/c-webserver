#include "model.h"
#include "socket_helper.h"

#include <unistd.h>

int client(char *host, char *port) {
	int clientfd;
	char buf[MAXLINE];

	clientfd = open_clientfd(host, port);
	
}

