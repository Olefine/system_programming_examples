#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main() {
	int epfd, ret;
	struct epoll_event event;

	epfd = epoll_create1(0);

	event.data.fd = STDOUT_FILENO;
	event.events = EPOLLOUT;

	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDOUT_FILENO, &event);

	if(ret)
		perror("epoll_ctl");

	int nr_events;
	nr_events = epoll_wait(epfd, &event, 1, 1000);

	if(nr_events < 0) {
		perror("epoll");
	} else {
		//write to stdout, because we epoll only stdout stream, if we add more stream, we have to add resolver for multiple streams
		char buff[] = "Hello epoll\n";

		int ret = write(event.data.fd, buff, strlen(buff));
	
		if (ret == -1) {
			perror("write");
			return 1;
		}
	}

		
	printf("event = %d on fd= %d\n", event.events, event.data.fd);
}
