#pragma once // HTTP_HANDLER_H_

#define ERROR_TITLE "<html><title>Tiny Error</title>"

void doit(int fd);

void clienterror(int fd, char *cause, char* errnum, char* shortmsg, char* longmsg);

void read_requesthdrs();

int parse_uri(char* uri, char* filename, char* cgiargs);

