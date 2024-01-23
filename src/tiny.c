#include "model.h"
#include "http_handler.h"

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

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

