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

#define BUF_SIZE  2048

int cfd;
void handler(int signo)
{
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
	int local_port = 0;

    if(argc <= 2){
        fprintf(stderr,"Usage %s [ip] [port]\n",argv[0]);
        exit(1);
    }else if(argc==4)
      local_port = atoi(argv[3]);

    signal(SIGINT,handler);

    cfd = socket(AF_INET,SOCK_STREAM, 0);
    if(cfd<0){
        perror("sock create failed\n");
        return -1;
    }

    ret = setsockopt(cfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof on);
    if(ret<0){
        perror("setsockopt faileed.\n");
        return -1;
    }
	
    if(local_port){
	addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(atoi(argv[3]));
    ret = bind(cfd,(struct sockaddr*)&addr,sizeof addr);
    if(ret<0){
        perror("bind failed.\n");
        return -1;
    }
    	}
    inet_pton(AF_INET,argv[1],tmp_buf);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = *(unsigned int*)tmp_buf;
    addr.sin_port = htons(atoi(argv[2]));
    ret = connect(cfd,(struct sockaddr*)&addr,len);
    if(ret<0){
        perror("connect failed.\n");
        return -1;
    }
	printf("connect  %s, port %u success\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
    while(1){
        ret = send(cfd,wbuf,BUF_SIZE,0);
        if(ret<=0){
            close(cfd);
            break;
        }
		memset(wbuf,0,BUF_SIZE);
		sleep(3);
        	}
    
    return 0;
}
