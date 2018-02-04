#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
  
int main(int argc, char* argv[])
{
    pid_t pid;
    int execv_ret;
    sigset_t mask;
    sigset_t orig_mask;
    struct timespec timeout;
  
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
  
    if (sigprocmask(SIG_BLOCK, &mask, &orig_mask) < 0){
        perror("sigprocmaks");
        return 1;
    }
  
    pid = fork();
  
    if (pid == 0){
	
	fprintf(stderr,"%d", getpid());

	printf("%s\n", argv[1]);

        return execl(argv[1], argv[1], argv[2], NULL); // run other program
    }
    else if (pid > 0){
        timeout.tv_sec = 10;
        timeout.tv_nsec = 0;
  
        do{
            if (sigtimedwait(&mask, NULL, &timeout) < 0){
                if (errno == EINTR)
                    continue;
                else if (errno = EAGAIN){
                    printf("Timeouted, kill child\n");
                    kill(pid, SIGKILL);
                    break;
                }
                else{
                    perror("sigtimedwait");
                    return 1;
                }
            }
            break;
        } while (1);
  
        waitpid(pid, &execv_ret, 0);
    }
    else{
        perror("fork");
        return 1;
    }
  
    return 0;
}
