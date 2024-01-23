#pragma once // TINY_H_

// handle the http request on fd socket
void doit(int fd);

void serve_static(int fd, char *filename, int filesize);

void serve_dynamic(int fd, char *filename, char* cgiargs);

void get_filetype(char* filename, char* filetype);

