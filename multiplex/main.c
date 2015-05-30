#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 3
#define BUFF_LEN 1024

int main(int argc, char **argv) {
	struct timespec tv;
	fd_set readfds;
	fd_set writefds;

	FD_ZERO(&readfds);
	FD_ZERO(&writefds);

	FD_SET(STDIN_FILENO, &readfds);
	FD_SET(STDOUT_FILENO, &writefds);

	tv.tv_sec = TIMEOUT;
	tv.tv_nsec = 0;

	int ret;
	try_select:

	ret = pselect(STDIN_FILENO + STDOUT_FILENO + 1,
				  &readfds,
				  &writefds, NULL, &tv, NULL);
	if(ret) {
		if(FD_ISSET(STDIN_FILENO, &readfds)) {
			char buff[BUFF_LEN];
			int len;

			len = read(STDIN_FILENO, buff, BUFF_LEN);
			if(len == -1) {
				perror("read");
				return 1;
			}

			if(len) {
				buff[len] = '\0';
				printf("read: %s\n", buff);
				FD_ZERO(&readfds);
				goto try_select;
			}
		}

		if(FD_ISSET(STDOUT_FILENO, &writefds)) {
			char buff[] = "Hello world\n";
			size_t len;
			len = write(STDOUT_FILENO, buff, 12);
			if(len == -1) {
				perror("write");
				return 1;
			}

			FD_ZERO(&writefds);
			goto try_select;
		}

	}

	return 0;
}
