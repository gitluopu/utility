#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void handler(int signum, siginfo_t *info,void *arg)
{
    int status;
	wait(&status);
    printf("%d,%d,status=%d\n",signum,info->si_signo,status);
}
int main(void)
{
    struct sigaction siga;
	pid_t pid;
	int ret;
    siga.sa_flags=SA_SIGINFO;
    siga.sa_sigaction = handler ;
    sigaction(SIGCHLD,&siga,NULL);
    pid = fork();
	if(pid<0){
		perror("fork faield.\n");
		return -1;
		}else if(pid==0){
		sleep(3);
		exit(2);
			}
		printf("child pid = %d\n",pid);
		while(1){
			sleep(3);
			}
    return 0;
}
