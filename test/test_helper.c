#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "../src/socket_helper.h"

int main(void) {
	int fd0, fd1, fd2, fd3;
	assert((fd0=open_clientfd("www.bilibili.com", "40"))!=-1);
	assert((fd1=open_clientfd("www.google.com", "40"))==-1);
	assert((fd2=open_serverfd("11111"))!=-1);
	assert((fd3=open_serverfd("1"))==-1);
	close(fd0);
	close(fd1);
	close(fd2);
	return 0;
}

