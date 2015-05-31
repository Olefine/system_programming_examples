#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	int status;
	pid_t pid;

	if(!fork())
		return 1;

	//returns finished children pid
	pid = wait(&status);
	if(pid == -1)
		perror("wait");

	printf("pid: %d\n", pid);

	if(WIFEXITED(status))
		printf("Normal exited, status = %d\n", WEXITSTATUS(status));

	if(WIFSIGNALED(status))
		printf("Terminated by signal, sig = %d%s\n", WTERMSIG(status), WCOREDUMP(status) ? " (core dump) " : " ");

	if(WIFSTOPPED(status))
		printf("Stopped, stopsig = %d\n", WSTOPSIG(status));

	if(WIFCONTINUED(status))
		printf("Continued\n");

	return 0;
}

