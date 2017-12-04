//#include<linux/in.h>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<netinet/tcp.h>
#include<string.h>
#include<arpa/inet.h>

#define BUF_SIZE  1024

int cfd;
int sfd;
void handler(int signo)
{
  close(sfd);
  close(cfd);
}
int main(int argc, char *argv[])
{
    int ret,on=1,len;
    unsigned char buf[4];
    len = sizeof(struct sockaddr);
    len = sizeof(struct sockaddr);
    struct sockaddr_in addr;
	char rbuf[BUF_SIZE]={0},wbuf[BUF_SIZE]={0};
	char tmp_buf[4];

    if(argc != 2){
        fprintf(stderr,"Usage %s [port]\n",argv[0]);
        exit(1);
    }

    signal(SIGINT,handler);

    sfd = socket(AF_INET,SOCK_STREAM, 0);
    if(sfd<0){
        perror("sock create failed\n");
        return -1;
    }

    ret = setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof on);
    if(ret<0){
        perror("setsockopt faileed.\n");
        return -1;
    }
	
    
	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(atoi(argv[1]));
    ret = bind(sfd,(struct sockaddr*)&addr,sizeof addr);
    if(ret<0){
		close(sfd);
        perror("bind failed.\n");
        return -1;
    }
    
  ret = listen(sfd,5);
  if(ret<0){
  	close(sfd);
  	perror("listen");
	return -1;
  	}
  cfd = accept(sfd,NULL,NULL);
  if(cfd<0){
  	perror("accept.");
	close(sfd);
	return -1;
  	}
    while(1){
        ret = recv(cfd,rbuf,BUF_SIZE,0);
        if(ret<=0){
            close(cfd);
            break;
        }
		memset(rbuf,0,BUF_SIZE);
        	}
    
    return 0;
}
