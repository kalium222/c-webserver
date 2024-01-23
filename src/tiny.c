#include "model.h"
#include "http_handler.h"
#include "tiny.h"

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

void doit(int fd) {
	// Whether this request is static
	int is_static;
	// lots of buffers
	char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
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

	// Parse URI from GET
	is_static = parse_uri(uri, filename, cgiargs);
	if (stat(filename, &sbuf)<0) {
		clienterror(fd, filename, "404", "Forbidden", 
				"There is no r18 things...");
		return;
	}

	if (is_static) {
		if (!(S_ISREG(sbuf.st_mode)) ||
			!(S_IRUSR & sbuf.st_mode)) {
			clienterror(fd, filename, "403", "Forbidden",
				"I cannot reach this file!");
			return;
		}
		serve_static(fd, filename, sbuf.st_size);
	} else {
		if (!(S_ISREG(sbuf.st_mode)) || 
			!(S_IXUSR & sbuf.st_mode)) {
			clienterror(fd, filename, "403", "Forbidden",
				"I cannot run this program");
			return;
		}
		serve_dynamic(fd, filename, cgiargs);
	}
	return;
}

