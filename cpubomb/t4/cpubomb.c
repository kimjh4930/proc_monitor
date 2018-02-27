#include "stdio.h"
#include <stdlib.h>
#include <pthread.h> 

#define TOTALFORK 4

int doBomb(void *arg){

unsigned long core_num = *(int*)arg + 1;
unsigned long mask = 1 << core_num;

if(pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) <0 ){
}

int i=4196016,j=32767,l,k,m,jj;jj=2342;
k= 31455;l= 16452;m= 9823;
long a;
for(a=0;a<100000000;a++){
m = m^l;k = (k/m * jj) % i; l=j*m*k;
i = (j * k)^m ;k = (k/m * jj) % i;m = m^l;
m = m^l;i = (j * k)^m ;k = (k/m * jj) % i;
m=i*i*i*i*i*i*i;// m=k*l*jj*l;
m = m^l;k = (k/m * jj) % i;l=j*m*k;i = (j * k)^m ;
l = (k/m * jj) % i;m = m^l;m = m^l;i = (j * k)^m ;
k = (k/m * jj) % i; m=k*k*k*k*k - m/i; 
if(a%5000 == 0) usleep(120);
}
}

main(int argc, char* argv[]){
	pthread_t thread[4];
        int joinStatus;

	int i=0;
	int thread_num=atoi(argv[1]);

	for(i=0; i<thread_num; i++){
		pthread_create(&thread[i], NULL, doBomb, &i);
	}
	for(i=0; i<thread_num; i++){
        	pthread_join(thread[i], (void**)&joinStatus);
	}

}
