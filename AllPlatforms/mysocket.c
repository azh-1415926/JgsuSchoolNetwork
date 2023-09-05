#include "mysocket.h"

/* 显示错误并退出程序 */
static void myError(const char* err)
{
    #if _WIN32
        printf("%s\n",err);
    #elif __linux__
        perror(err);
    #endif
    exit(1);
}

#if _WIN32

/* 初始化套接字，Windows 特有 */
bool initalizeSocket(){
    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2),&wsadata)==0)
        return true;
    myError("WSAStart error!");
}

#endif

/* 初始化 server_addr，用指定 af、ip、port 赋值 */
struct sockaddr_in* setSockaddr(struct sockaddr_in* server_addr, unsigned int size, int af, const char* server_ip, unsigned int server_port)
{
    /* 清空 */
    memset(server_addr,0,size);
    server_addr->sin_family=af;
    server_addr->sin_port=htons(server_port);
    #if _WIN32
        server_addr->sin_addr.S_un.S_addr=inet_addr(server_ip);
    #elif __linux__
        inet_pton(af,server_ip,&server_addr->sin_addr.s_addr);
    #endif
    return server_addr;
}

/* 创建一个套接字，返回描述符 */
SOCKET_FD Socket(int af,int type,int protocol)
{
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

/* 连接到服务器 */
bool Connect(SOCKET_FD s,struct sockaddr* server_addr,socklen_t server_len)
{
    int status;
    #if __linux__
        int flags;
        flags=fcntl(s,F_GETFL);
        fcntl(s,F_SETFL,flags|O_NONBLOCK);
    #endif
        status=connect(s,server_addr,server_len);
    #if _WIN32
        if(status==SOCKET_ERROR)
        {
            closeSocket(s);
            myError("connect error!");
        }
    #elif __linux__
        if(status<0)
        {
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

/* 设置 send、receive 超时时长 */
void setTimeout(SOCKET_FD s,int time)
{
    struct timeval timeout={time,0};
    setsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(char*)&timeout,sizeof(struct timeval));
    /* 不知道为什么 Windows 下设置这个会有问题，暂时不用 */
    #if __linux__
        setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));
    #endif
}

/* 关闭套接字 */
void closeSocket(SOCKET_FD s)
{
    #if _WIN32
        closesocket(s);
        WSACleanup();
    #elif __linux_
        close(s);
    #endif
}