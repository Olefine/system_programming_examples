#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>

int fragmental_write();
int fragmental_read();

int main(int argc, char **argv) {
	fragmental_write();
	fragmental_read();

	return 0;
}

int fragmental_read() {
	char foo[48], bar[51], baz[49];
	struct iovec iov[3];
	ssize_t nr;
	int fd, i;

	fd = open("buccaneer", O_RDONLY);

	if(fd == -1) {
		perror("open");
		return 1;
	}

	iov[0].iov_base = foo;
	iov[0].iov_len = sizeof(foo);

	iov[1].iov_base = bar;
	iov[1].iov_len = sizeof(bar);

	iov[2].iov_base = baz;
	iov[2].iov_len = sizeof(baz);

	nr = readv(fd, iov, 3);
	if(nr == -1) {
		perror("readv");
		return 1;
	}

	for(i = 0; i < 3; i++)
		printf("%d: %s", i, (char *)iov[i].iov_base);

	if(close(fd)) {
		perror("close");
		return 1;
	}

	return 0;
}

int fragmental_write() {
	struct iovec iov[3];
	ssize_t nr;
	int fd, i;

	char *buff[] = {
		"The term buccaneer comes from the word boucan.\n",
		"A boucan is a wooden frame used for cooking mear.\n",
		"Buccaneer is the West Indies name for a pirate.\n"
	};

	fd = open("buccaneer", O_WRONLY | O_CREAT | O_TRUNC, "r");
	if(fd == -1) {
		perror("creat");
		return 1;
	}

	for(i = 0; i < 3; i++) {
		iov[i].iov_base = buff[i];
		iov[i].iov_len = strlen(buff[i]) + 1;
	}

	nr = writev(fd, iov, 3);

	if(nr == -1) {
		perror("writev");
		return 1;
	}
	printf("Wrote %d bytes\n", nr);

	if(close(fd)) {
		perror("close");
		return 1;
	}

	return 0;
}
