#pragma once // HTTP_HANDLER_H_

#define ERROR_TITLE "<html><title>Tiny Error</title>"

// handle the http request on fd socket
void doit(int fd);

// write error to fd socket according to the 
// following things
void clienterror(int fd, char *cause, char* errnum, char* shortmsg, char* longmsg);

void read_requesthdrs();

// return whether the request is static
int parse_uri(char* uri, char* filename, char* cgiargs);

