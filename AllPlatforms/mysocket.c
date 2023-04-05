#include "mysocket.h"
static void myError(const char* err){
    #if _WIN32
        printf("%s\n",err);
    #elif __linux__
        perror(err);
    #endif
    exit(1);
}
struct sockaddr_in* setSockaddr(struct sockaddr_in* server_addr,int af,const char* server_ip,int server_port){
    memset(server_addr,0,sizeof(struct sockaddr_in));
    server_addr->sin_family=af;
    server_addr->sin_port=htons(server_port);
    #if _WIN32
        server_addr->sin_addr.S_un.S_addr=inet_addr(server_ip);
    #elif __linux__
        inet_pton(af,server_ip,&server_addr->sin_addr.s_addr);
    #endif
    return server_addr;
}
SOCKET_FD Socket(int af,int type,int protocol){
    SOCKET_FD s=socket(af,type,protocol);
    #if _WIN32
        if(s!=INVALID_SOCKET)
            return s;
        WSACleanup();
    #elif __linux__
        if(s>0)
            return s;
    #endif
    myError("socket error!");
}
bool Connect(SOCKET_FD s,struct sockaddr* server_addr,socklen_t server_len){
    int status;
    #if __linux__
        int flags;
        flags=fcntl(s,F_GETFL);
        fcntl(s,F_SETFL,flags|O_NONBLOCK);
    #endif
        status=connect(s,server_addr,server_len);
    #if _WIN32
        if(status==SOCKET_ERROR){
            closeSocket(s);
            myError("connect error!");
        }
    #elif __linux__
        if(status<0){
            if(errno!=EINPROGRESS)
            {
                close(s);
                myError("connect error!");
            }
            printf("connect nonblock.\n");
        }
        fcntl(s,F_SETFL,flags);
    #endif
    return true;
}
void setTimeout(SOCKET_FD s,int time){
    struct timeval timeout={time,0};
    setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(struct timeval));
    #if __linux__
        setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
    #endif
}
void closeSocket(SOCKET_FD s){
    #if _WIN32
        closesocket(s);
        WSACleanup();
    #elif __linux_
        close(s);
    #endif
}
#if _WIN32
bool initalizeSocket(){
    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2),&wsadata)==0)
        return true;
    myError("WSAStart error!");
}
#endif