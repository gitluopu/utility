#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<syslog.h>
#include<stdlib.h>

#define pty_err(format,args...) syslog(LOG_ERR,format,##args)

int main(void)
{
   int fd,ret;
   char buf[16] = {0};
   char *ptr;
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
  printf("ptsname:%s\n",ptr);
    return 0;
	close_fd:
		close(fd);
		return -1;
}
