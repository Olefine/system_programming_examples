#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>


#undef _LINUX_LIMITS_H
#include <linux/limits.h>

int main(void) {
	pid_t pid;
	int i;

	//create new proc
	pid = fork();

	if(pid == -1)
		return -1;
	else if(pid != 0)
		exit(EXIT_SUCCESS);

	//create new session and proc groups
	if(setsid() == -1)
		return -1;

	//chage dir to root
	if(chdir("/") == -1)
		return -1;

	//close all opened files
	for(i = 0; i < NR_OPEN; i++)
		close(i);

	//piping all fds to /dev/null
	open("/dev/null", O_RDWR);
	dup(0);
	dup(0);

	return 0;
}
