#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


int main(void)
{
    pid_t pid;
    int fd = open("hello.txt",O_RDWR|O_CREAT,0664);
    if(fd<0){
        perror("lopen failed\n");
        return -1;
    }
    pid = vfork();
    if(pid<0){
        perror("vfork faield.\n");
        return -1;
    }else if(pid==0){
        write(fd,"hello,world\n",16);
        sleep(3);
        kill(getppid(),SIGINT);
        exit(0);
    }
    pause();
    return 0;
}
