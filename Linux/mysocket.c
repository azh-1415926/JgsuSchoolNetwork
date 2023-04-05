#include "mysocket.h"
#include<fcntl.h>
#include<errno.h>
void myError(const char *err){
    perror(err);
    exit(-1);
}
struct sockaddr_in* setSockaddr(struct sockaddr_in* server_addr,int af,const char* server_ip,int server_port){
    server_addr->sin_family=AF_INET;
    inet_pton(af,server_ip,&server_addr->sin_addr.s_addr);
    server_addr->sin_port=htons(server_port);
    return server_addr;
}
int Socket(int domain,int type,int protocol){
    int fd=socket(domain,type,protocol);
    if(fd<0){
        myError("socket error!");
    }
    return fd;
}
int Connect(int fd,struct sockaddr* server_addr,socklen_t server_len){
    int flags=fcntl(fd,F_GETFL);
    fcntl(fd,F_SETFL,flags|O_NONBLOCK);
    int status=connect(fd,server_addr,server_len);
    if(status<0){
        if(errno!=EINPROGRESS)
        {
            close(fd);
            myError("connect error!");
        }
        printf("connect nonblock.\n");
    }
    fcntl(fd,F_SETFL,flags);
    return status;
}
int SetSendTimeOut(int fd,int time){
    struct timeval timeout={time,0};
    int ret=setsockopt(fd,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(struct timeval));
    if(ret==-1){
        close(fd);
        myError("SetSendTimeOut failed,setsockopt error!");
    }
    return 1;
}
int SetReceiveTimeOut(int fd,int time){
    struct timeval timeout={time,0};
    int ret=setsockopt(fd,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
    if(ret==-1){
        close(fd);
        myError("SetSendTimeOut failed,setsockopt error!");
    }
    return 1;
}   
int Send(int fd,const char *buf,int size,int flag){
    int ret=send(fd,buf,size,flag);
    if(ret==-1){
        close(fd);
        myError("send error!");
    }
    return 1;
}
int Recv(int fd,char *buf,int size,int flag){
    int len=recv(fd,buf,size,flag);
    if(len==-1){
        close(fd);
        myError("recv error!");
    }
    return len;
}
int Close(int fd){
    int ret=close(fd);
    if(ret==-1){
        close(fd);
        myError("close error!");
    }
    return 1;
}