
#include<stdio.h>
#include<sys/socket.h>
#include<netpacket/packet.h>
#include<net/ethernet.h>
#include<linux/in.h>
#include<string.h>
#include<stdlib.h>
#include<sys/mmap.h>
#include<sys/types.h>

#define BUF_SIZE 16*1024*1024
#define PER_PACKET_SIZE 2048
int main(int argc,char *argv[])
{
 int fd,ret;
 int version = TPACKET_V1;
 struct tpacket_req req;
 char *buf;
 fd = socket(AF_PACKET,SOCK_DGRAM,htons(ETH_P_IP));
 if(fd<0){
 	perror("socket failed");
	return -1;
 	}
 ret = setsockopt(fd,SOL_PACKET,PAKCET_VERSION,&version,sizeof(int));
 if(ret<0){
 	perror("setsockopt failed.\n");
	return -1;
 	}
 req.tp_block_size = 4096;
 req.tp_block_nr = 128;
 req.tp_frame_size = 2048;
 req.tp_fram_nr = 128;
 ret = setsockopt(fd,SOL_PACKET,PACKET_RX_RING,(void*)&req,sizeof(req));
 if(ret<0){
 	perror("setsockopt req failed.\n");
	return -1;
 	}
 buf = mmap(fd, BUFFER_SIZE, PROT_READ, MAP_SHARED, fd, 0);
 if(buf==MAP_FAILED){
 	perror("mmap");
	return -1;
 	}	
 while(1){
 	struct tpacket_hdr *ph = (struct tpacket_hdr*)(buf);
	struct pollfd pfd;
	if(ph->tp_status==TP_STATUS_USER)
		printf();
 	}
    pfd.fd = fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	ret = poll(&pfd,1,-1);
	if(ret<0){
		perror("poll");
		close(fd);
		return -1;
		}
	for(i=0;i<req.tp_fram_nr;i++){
		struct tpacket_hdr *ph = ();
		if(ph->tp_status==TP_STATUS_KERNEL)
			break;
		handle_data();
		ph->tp_len = 0;
		ph->tp_status = IP_STATUS_KERNEL;
		
		}
return 0;
}











































