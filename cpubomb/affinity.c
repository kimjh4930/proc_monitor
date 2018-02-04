/**
 * ytest without ytracer
 * 	  with sched_setaffinity
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <sched.h>
#include <getopt.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_BUFFER_LEN	1024

int main(int argc, char* argv[]) {
	pid_t pid;
	int i, j, status;
	char c_tracer[50], arg[10];
	pthread_t t_id;

	int max_cpu = -1;
	int cpu = -1;
	int opt;

	while ((opt = getopt(argc, argv, "n:c:")) != -1) {
		switch (opt) {
			case 'c':
				cpu = atoi(optarg);
				break;
			case 'n':
				max_cpu = atoi(optarg);
				break;
			case '?':
			default:
				//print_help(argv[0]);
				printf("fail\n");
				exit(EXIT_FAILURE);
				break;
		}
	}

	pid = fork();
	if (pid == 0) {
		cpu_set_t mask;

		CPU_ZERO(&mask);
		CPU_SET(cpu, &mask);
		sched_setaffinity(getpid(), sizeof(mask), &mask);
		sprintf(arg, "%d", getpid());
		// cpubomb
		execl("./cpubomb", "./cpubomb", (char*)0);
		//execl("ramsmp-3.5.0-custom/ramsmp", "ramsmp", "-b1", "-p4",  (char*)0);
	} else if (pid > 0) {
		pid = wait(&status);
	}

	return 0;
}
