
/********************tcp_keep_alive****************************/
    #include<netinet/tcp.h>
    ret = setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,&on,sizeof on);
    if(ret<0){
        return -1;
    }

    ret = setsockopt(sock,SOL_TCP,TCP_KEEPIDLE,&time,sizeof on);
    if(ret<0){
        return -1;
    }
    ret = setsockopt(sock,SOL_TCP,TCP_KEEPINTVL,&intvl,sizeof on);
    if(ret<0){
        return -1;
    }
    ret = setsockopt(sock,SOL_TCP,TCP_KEEPCNT,&probes,sizeof on);
    if(ret<0){
        return -1;
    }
    ret = setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof on);
    if(ret<0){
        return -1;
    }


	
