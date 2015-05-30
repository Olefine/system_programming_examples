#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void read_n_bytes_from_console();
void read_from_file(const char *filename);
int write_char_to_stdout(char ch, int newline);
int append_str_to_file(const char *str, const char *filename);

int get_stream_fd(FILE *stream);
int write_to_file_using_syscalls(const char *filename, const char *str);

int main() {
	const char *filename = "file";
	const char *str = "Egor";
	FILE *stream = fopen(filename, "w");

	if(!write_to_file_using_syscals(stream, str)) {
		perror("write_to_file_with_syscalls");
		return 1;
	}

	return 0;
}

int get_stream_fd(FILE *stream) {
	int fd;

	if((fd = fileno(stream)) == -1) {
		perror("getfilenot");
		exit(1);
	}

	return fd;
}

int write_to_file_using_syscals(FILE *stream, const char *str) {
	int fd = get_stream_fd(stream);
	int ret;
	
	ret = write(fd, str, sizeof(str));
	fsync(fd);	

	if(!close(fd)) {
		printf("Success!\n");
		return 0;
	} else {
		return errno;
	}

}

void read_from_file(const char *filename) {
	int fd;
	FILE *stream;

	fd = open(filename, O_RDONLY);

	if(fd == -1) {
		perror("open:");
		return 1;
	}

	stream = fdopen(fd, "r");

	if(!stream) {
		perror("error");
		return 1;
	} else {
		int ch;
		while(ch != EOF) {
			ch = fgetc(stream);
			printf("%c", (char) ch);
		}
	}

	fclose(stream);
	printf("\n");
}

void read_n_bytes_from_console() {
	int fd;
	FILE *stream;

	stream = fdopen(STDIN_FILENO, "r");
	const buff_size = 64;
	char buff[buff_size];
	int nread = fread(buff, sizeof(buff), 1, stream);
	
	if(nread == 0) {
		perror("read:");
		return 1;
	} else {
		printf("%d symbols readed\n", nread * sizeof(buff));
	}

	fclose(stream);

	int j = 0;
	for(char i = 0; i < buff_size; i++, j++) {
		printf("%c", (char)buff[i]);
		if(((j % 3) == 0) && (j != 0))
			printf(" ");
	}


	printf("\n");
}

int write_char_to_stdout(char ch, int newline) {
	int ret;
	int len = sizeof(ch);


	ret = write(STDOUT_FILENO, &ch, len);

	if(newline){
		printf("\n");
	}

	if(ret == -1) {
		printf("write");
		return 1;
	}

	return 0;
}

int append_str_to_file(const char *str, const char *filename) {
	FILE *stream;
	stream = fopen(filename, "a");

	if(stream == -1) {
		perror("open");
		return -1;
	}

	if(fputs(str, stream) == EOF)
		perror("write");
		
	fclose(stream);
}

