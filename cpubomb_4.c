#include "stdio.h"
#include <stdlib.h> 

#define TOTALFORK 4

int doBomb(){

pid_t pid;
pthread_t tid;

pid = getpid();
tid = pthread_self();

printf("pid : %u\t tid : %u\n", pid, tid);

int i=4196016,j=32767,l,k,m,jj;jj=2342;
k= 31455;l= 16452;m= 9823;
long a;
for(a=0;a<1000000000;a++){
m = m^l;k = (k/m * jj) % i; l=j*m*k;
i = (j * k)^m ;k = (k/m * jj) % i;m = m^l;
m = m^l;i = (j * k)^m ;k = (k/m * jj) % i;
m=i*i*i*i*i*i*i;// m=k*l*jj*l;
m = m^l;k = (k/m * jj) % i;l=j*m*k;i = (j * k)^m ;
l = (k/m * jj) % i;m = m^l;m = m^l;i = (j * k)^m ;
k = (k/m * jj) % i; m=k*k*k*k*k - m/i; 
}}

main(){
	pthread_t thread[4];
        int joinStatus;
        //int f1=1,f2=2,f3=3,f4=4;

        pthread_create(&thread[0], NULL, doBomb, NULL);
        pthread_create(&thread[1], NULL, doBomb, NULL);
        pthread_create(&thread[2], NULL, doBomb, NULL);
        pthread_create(&thread[3], NULL, doBomb, NULL);

        pthread_join(thread[0], (void**)&joinStatus);
        pthread_join(thread[1], (void**)&joinStatus);
        pthread_join(thread[2], (void**)&joinStatus);
        pthread_join(thread[3], (void**)&joinStatus);
}
