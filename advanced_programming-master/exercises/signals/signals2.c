#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig) {
	printf("PID %i - handling the signal %i\n", getpid(), sig);
}

int main(int argc, char* argv[]) {
	int pid;
	
	if ( (pid = fork()) < 0 ){
		perror(argv[0]);
		return -1;
	} else if (pid == 0) {
		int i = 0;
		while(1) {
			printf("PID %i - PPID %i - i = %i\n", getpid(), getppid(), i);
			sleep(2);
			i++;
		}
		exit(0);
	} else {
		sleep(10);
		printf("PID %i killing to PID %i\n", getpid(), pid);
		kill(pid, SIGTERM);
	}
	return 0;
}
