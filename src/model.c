#include "model.h"
#include "socket_helper.h"

#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void echo(int fd);

int client(char *host, char *port) {
	int clientfd;
	char buf[MAXLINE];

	clientfd = open_clientfd(host, port);
	while (fgets(buf, MAXLINE, stdin)!=NULL) {
		write(clientfd, buf, strlen(buf));
		read(clientfd, buf, MAXLINE);
		fputs(buf, stdout);
	}
	close(clientfd);
	return 0;
}

int server(char *port) {
	int listenfd, connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	char client_hostname[MAXLINE], client_port[MAXLINE];

	listenfd = open_serverfd(port);
	/*while (1) {*/
		clientlen = sizeof(struct sockaddr_storage);
		connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
		getnameinfo((struct sockaddr*) &clientaddr, clientlen,
			   	client_hostname, MAXLINE, client_port, MAXLINE, 0);
		printf("Connected to (%s, %s)\n", client_hostname, client_port);
		echo(connfd);
		close(connfd);
	/*}*/
	return 0;
}

void echo(int fd) {
	size_t n;
	char buf[MAXLINE];

	while ((n=read(fd, buf, MAXLINE))!=0) {
		printf("server received %d bytes\n", (int)n);
		write(fd, buf, n);
	}
}

