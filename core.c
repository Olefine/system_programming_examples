#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char *get_filename(int argc, char **argv) {
	char *filename;

	for(int i = 0; i < argc; i++)
		if(argv[i][1] == 'f') {
			filename = argv[i+1];
			break;
		}
	
	return filename;
}

int main(int argc, char **argv) {
	char *filename = get_filename(argc, argv);

	int fd = open(filename, O_RDONLY);

	if(fd == -1) {
		perror("open");
		exit(-1);
	}

	off_t len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	char buffer[len];

	ssize_t bytes_readed;
	bytes_readed = read(fd, buffer, len);

	if(bytes_readed == -1)
		perror("read");

	char *p = buffer;

	for(int i = 0; i < len; i++)
		printf("%c", p[i]);


	return 0;
}

