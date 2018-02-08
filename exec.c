#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

double getTimeDiff(unsigned int);

int main(int argc, char* argv[]){

	int child, status, pid;

	time_t start=0, end=0;

	pid = vfork();

	start = clock();
	if(pid == 0){

		fprintf(stderr, "%d", getpid());

		//execl("./iozone", "./iozone", "-a", "-s", "4G", "-g", "4G", "-r", "16M", "-i", "0", "-i", "1", NULL);
		//execl("./iozone","./iozone"," -a -s 2G -g 2G -r 16M -i 0 -i 1",NULL);

		execl("./run/cpubomb_100", "./run/cpubomb_100", "1", NULL);
		exit(1);
	}else{
		getTimeDiff(0);
		child = wait(&status);
		
		printf("time : %lf \n", getTimeDiff(1));
		printf("child close\n");
	}
}

double getTimeDiff(unsigned int nFlag){
	const long long NANOS = 1000000000L;

	static struct timespec start, end;
	static double retDiff = 0;

	int sec=0;
	int nsec=0;

	if(nFlag == 0){
		retDiff = 0.0;
		if(-1 == clock_gettime(CLOCK_MONOTONIC, &start))
			printf("Failed to call clock_gettime\n");
	}else{
		if(-1 == clock_gettime(CLOCK_MONOTONIC, &end))
			printf("Failed to call clock_gettime\n");

		//tv_sec  : second
		//tv_nsec : nanoseconds

		sec = end.tv_sec - start.tv_sec;
		nsec = end.tv_nsec - start.tv_nsec;

		retDiff = (double)sec + (double)nsec/NANOS;
	}

	return retDiff;
}
