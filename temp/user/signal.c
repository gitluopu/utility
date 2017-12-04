#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void handler(int signum, siginfo_t *info,void *arg)
{
    printf("%d,%d\n",signum,info->si_signo);
    exit(1);
}
int main(void)
{
    struct sigaction siga;
    siga.sa_flags=SA_SIGINFO;
    siga.sa_sigaction = handler ;
    sigaction(SIGINT,&siga,NULL);
    while(1){
        sleep(3);
    }
    return 0;
}
