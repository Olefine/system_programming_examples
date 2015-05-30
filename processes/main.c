#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>

void print_process_info();
int run_vim_in_current_process();
void run_vim_in_child_proc();

int main(int argc, char **argv) {
	run_vim_in_child_proc();
	return 0;
}

void print_process_info() {
	printf("Current process pid %jd\n",(intmax_t) getpid());
	printf("Parent process pid %jd\n", (intmax_t) getppid());
}

int run_vim_in_current_process() {
	int ret;
	char path[] = "/usr/bin/vim";

	ret = execl(path, "vim", NULL);

	if(ret == -1) {
		perror("exec vim");
		return 1;
	}

	return 0;
} 

void run_vim_in_child_proc() {
	pid_t cpid;
	cpid = fork();

	if(cpid == -1){
		perror("create_child_proc");
		return 1;
	}

	//zero pid indicates that process is child
	if(!cpid) {
		int ret;
		char *args[] = {"vim", NULL};

		ret = execv("/usr/bin/vim", args);

		if(ret == -1) {
			perror("execv");
			exit(EXIT_FAILURE);
		}
	}
}
