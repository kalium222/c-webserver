#include "../src/http_handler.h"

#include <unistd.h>

int main(void) {
	clienterror(STDOUT_FILENO, "Cause", "ErrorNumber", "ShortMsg", "LongMsg");
	return 0;
}

