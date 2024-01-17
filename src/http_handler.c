#include "http_handler.h"
#include "model.h"

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void doit(int fd) {
	int is_static;
	/*struct stat sbuf;*/
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char filename[MAXLINE], cgiargs[MAXLINE];

	fscanf(fdopen(fd, "r"), "%s %s %s", method, uri, version);
	printf("Request headers:\n");
	printf("%s %s %s", method, uri, version);
	
	if (strcasecmp(method, "GET")) {
		// TODO: error
		return;
	}

	// TODO: read request


}

void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg) {
	char buf[MAXLINE], body[MAXLINE];

	sprintf(body, ERROR_TITLE);
	sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
	sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
	sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
	sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

	sprintf(buf, "HTTP/1.0 %s %s \r\n", errnum, shortmsg);
	write(fd, buf, strlen(buf));
	sprintf(buf, "Content-type: test/html\r\n");
	write(fd, buf, strlen(buf));
	sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
	write(fd, buf, strlen(buf));
	write(fd, body, strlen(body));
	return;
}

