#include "http_handler.h"
#include "model.h"

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void doit(int fd) {
	// Whether this request is static
	int is_static;
	// lots of buffers
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char filename[MAXLINE], cgiargs[MAXLINE];
	// file state of filename
	struct stat sbuf;

	fscanf(fdopen(fd, "r"), "%s %s %s", method, uri, version);
	printf("Request headers:\n");
	printf("%s %s %s", method, uri, version);
	
	if (strcasecmp(method, "GET")) {
		clienterror(fd, method, "501", "Not Implemented", 
				"Tiny does not implement this method");
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

int parse_uri(char *uri, char *filename, char *cgiargs) {
	if (!strstr(uri, "cgi-bin")) {
		// static
		strcpy(cgiargs, "");
		strcpy(filename, ".");
		strcat(filename, uri);
		if (uri[strlen(uri)-1]=='/') {
			strcat(filename, "home.html");
		}
		return 1;
	} else {
		// dynamic
		char* p=index(uri, '?');
		if (p) {
			strcpy(cgiargs, p+1);
			*p = '\0';
		} else {
			strcpy(cgiargs, "");
		}
		strcpy(filename, ".");
		strcpy(filename, uri);
		return 0;
	}
}

