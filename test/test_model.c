#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "../src/model.h"

#define PORT "11111"

// how to test it?
int main(void) {
	pid_t pid;
	pid = fork();
	if (pid<0) {
		fprintf(stderr, "Fork error\n");
		return 1;
	} else if (pid==0) {
		// child
		client("xps-13-9300", PORT);
	} else {
		// parent
		server(PORT);
	}
	return 0;
}

