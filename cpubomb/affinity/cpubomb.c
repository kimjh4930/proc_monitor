#include "stdio.h" 
#include <unistd.h>
int main(int argc, char* argv[]){int i=4196016,j=32767,l,k,m,jj;jj=2342;
k= 31455;l= 16452;m= 9823;long a;for(a=0;a<100000000;a++)
//k= 31455;l= 16452;m= 9823;long a;for(a=0;a<=5000;a++)
{ m = m^l;k = (k/m * jj) % i; l=j*m*k;
i = (j * k)^m ;k = (k/m * jj) % i;m = m^l;
m = m^l;i = (j * k)^m ;k = (k/m * jj) % i;
m=i*i*i*i*i*i*i;// m=k*l*jj*l;
m = m^l;k = (k/m * jj) % i;l=j*m*k;i = (j * k)^m ;
l = (k/m * jj) % i;m = m^l;m = m^l;i = (j * k)^m ;
k = (k/m * jj) % i; m=k*k*k*k*k - m/i; 
if(a % 5000 == 0) usleep(atoi(argv[1]));
}}
