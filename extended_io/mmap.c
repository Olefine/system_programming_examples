#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>

void print_pagesize();

int main(int argc, char **argv) {
	void *p;

	FILE *stream = fopen("buccaneer", "rw");

	errno = 0;
	p = mmap(0, 1, PROT_READ | PROT_WRITE, MAP_PRIVATE, fileno(stream), 0);
	if(!errno) {
		perror("mmap");
		return 1;
	}

	printf("char from memory - %c\n", (char *)p);
	return 0;
}

void print_pagesize() {
	printf("%ld bytes\n", sysconf(_SC_PAGESIZE));
}
