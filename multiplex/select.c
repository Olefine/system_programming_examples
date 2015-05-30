#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5
#define BUFF_LEN 1024

int main(int argc, char **argv) {
	struct timeval tv;
	fd_set readfds;
	int ret;

	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

	if(ret == -1) {
		perror("select");
		return 1;
	} else if(!ret) {
		printf("%d seconds elapsed\n", TIMEOUT);
		return 0;	
	}

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
		}

		return 0;
	}
	
}
