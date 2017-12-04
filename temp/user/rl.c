#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<syslog.h>
#include<string.h>
#include<errno.h>
#include<signal.h>
#include<stdlib.h>

#define pty_err(format,args...) syslog(LOG_ERR,format,##args)

static void child_handler(int arg)
{
int status;
wait(&status);
printf("status = %d\n",status);
}
int main(void)
{
   int fd,ret;
   char buf[16] = {0};
   char *ptr;
   pid_t pid;
   char rbuf[128];
   char wbuf[128];
   fd_set rfds;
   fd_set tfds;
   fd = open("/dev/ptmx",O_RDWR|O_NOCTTY);
   if(fd<0){
   	pty_err("open /dev/ptmx failed.\n");
	return -1;
   	}
   ret = grantpt(fd);
   if(ret<0){
   	pty_err("grantpt err.\n");
	goto close_fd;
   	}
   ret = unlockpt(fd);
   if(ret<0){
   	pty_err("unlockpt err.\n");
	goto close_fd;
   	}
  ptr = (char*)ptsname(fd);
  memcpy(buf,ptr,strlen(ptr)+1);
  signal(SIGCHLD,child_handler);
  pid=fork();
  if(pid<0){
  	pty_err("fork err.\n");
	goto close_fd;
  	}else if(pid==0){
  	close(0);
	close(1);
	close(2);
	close(fd);
	fd = open(buf,O_RDWR|O_NOCTTY);
	if(fd<0){
		pty_err("child open pts err.\n");
		exit(0);
		}
	dup(fd);
	dup(fd);
	execl("/bin/login","login",NULL);
  	exit(0);
  		}
	printf("child open pts %s\n",buf);
	FD_ZERO(&rfds);
	FD_SET(0,&rfds);
	FD_SET(fd,&rfds);
	while(1){
		tfds = rfds;
		ret = select(20,&tfds,NULL,NULL,NULL);
		if(ret<0){
			pty_err("select faield.err=%d\n",errno);
			goto close_fd;
			}
		if(FD_ISSET(fd,&tfds)){
		ret = read(fd,rbuf,128);
		if(ret<0){
			pty_err("parent read failed.\n");
			goto close_fd;
			}
		write(1,rbuf,ret);
			}
		if(FD_ISSET(0,&tfds)){
		ret = read(0,rbuf,128);
		if(ret<0){
			pty_err("parent read failed.\n");
			goto close_fd;
			}
		write(fd,rbuf,ret);
			}
		}
    return 0;
	close_fd:
		close(fd);
		return -1;
}
