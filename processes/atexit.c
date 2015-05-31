#include <stdio.h>
#include <stdlib.h>

void out() {
	printf("Bye bye bye...\n");
}

int main(int argc, char **argv) {
	atexit(out);
	printf("Hello and bye\n\n");
	return 0;
}
