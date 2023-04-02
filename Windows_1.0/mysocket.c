#include "mysocket.h"
#include <stdlib.h>
static void error(const char* err){
    printf("%s\n",err);
    exit(1);
}
void initalizeSockaddr_in(struct sockaddr_in* server_addr,int af,const char* ip,int port){
    memset(server_addr,0,sizeof(struct sockaddr_in));
    server_addr->sin_family=af;
    server_addr->sin_port=htons(port);
    server_addr->sin_addr.S_un.S_addr=inet_addr(ip);
}
bool initalizeSocket(){
    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2),&wsadata)==0)
        return true;
    error("WSAStart error!");
}
SOCKET Socket(int af,int type,int protocol){
    SOCKET s=socket(af,type,protocol);
    if(s!=INVALID_SOCKET)
        return s;
    WSACleanup();
    error("socket error!");
}
void Connect(SOCKET s,struct sockaddr* server_addr,int len){
    if(connect(s,server_addr,len)==0)
        return;
    error("connect error!");
}
void setTimeout(SOCKET s,int time){
    struct timeval timeout={time,0};
    setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(struct timeval));
    //setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
}
void closeSocket(SOCKET s){
    closesocket(s);
    WSACleanup();
}