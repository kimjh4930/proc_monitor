#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <sched.h>
 
void print_help(char *cmd) {
    printf("Usage: %s -n <cpu 개수> -c < 선호CPU>\n\n", cmd);
    printf("       CPU 개수 : CPU 코어 개수\n");
    printf("       선호 CPU : CPU 코어 번호 (0 부터 시작)\n\n");
    printf("       예 : 쿼드코어 CPU에서 3번째 코어를 사용하는 경우\n");
    printf("            $ %s -n 4 -c 2\n", cmd);
}
 
int main(int argc, char *argv[]) {
    unsigned int i = 0;
    pid_t pid;
    int max_cpu = -1;
    int cpu = -1;
    int opt;
 
    while ( (opt = getopt(argc, argv, "n:c:")) != -1 ) {
        switch ( opt ) {
            case 'c' :
                cpu = atoi(optarg);
                break;
            case 'n' :
                max_cpu = atoi(optarg);
                break;
            case '?' :
            default :
                print_help(argv[0]);
                exit(EXIT_FAILURE);
                break;
        }
    }
 
    if ( max_cpu < 1 || cpu < 0 || cpu >= max_cpu ) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
 
    if ( (pid = fork()) == 0 ) {
        cpu_set_t mask;
 
        CPU_ZERO(&mask);
        CPU_SET(cpu, &mask);
        pid = getpid();
        if ( sched_setaffinity(pid, sizeof(mask), &mask) ) {
            fprintf(stderr, "%d 번 CPU를 선호하도록 설정하지 못했습니다.\n",
                    cpu);
            exit(EXIT_FAILURE);
        }
        else {
            printf("%d 번 CPU를 선호하도록 설정했습니다.\n", cpu);
        }
 
        for ( i = 0; i < UINT_MAX; i++) {
        }
    }
    else {
        int status;
        waitpid(pid, &status, 0);
    }
 
    return EXIT_SUCCESS;
}
