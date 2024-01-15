#ifndef SOCKET_HELPER_H_
#define SOCKET_HELPER_H_

#define LISTENQ 1

int open_clientfd(char* hostname, char* port);

int open_serverfd(char* port);

#endif // SOCKET_HELPER_H_

