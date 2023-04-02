#include "mysocket.h"
#include "myhttp.h"
#define SERVER_IP "192.168.167.42"
#define SERVER_PORT 801
#define HOST "192.168.167.42:801"
#define URL "/eportal/portal/login"
int main(){
    SOCKET_FD s;
    char buf[512];
    struct sockaddr_in server_addr;
    setSockaddr(&server_addr,AF_INET,SERVER_IP,SERVER_PORT);
    printf("[*] SERVER_IP:%s\n[*] SERVER_PORT:%d\n",SERVER_IP,SERVER_PORT);
    #if _WIN32
        printf("[-] Winsock Initalize.\n");
        initalizeSocket();
    #endif
    struct httpMessage http;
    httpMessageInitalize(&http,sizeof(http),"GET",URL,"HTTP/1.1",HOST);
    memset(buf,0,sizeof(buf));
    createHttpMessage(buf,&http);
    httpMessageFree(&http);
    printf("[*] HttpRequestMessage:\n--------------\n%s\n--------------\n",buf);
    s=Socket(AF_INET,SOCK_STREAM,0);
    printf("[-] Connecting to SERVER...\n");
    Connect(s,(struct sockaddr*)&server_addr,sizeof(server_addr));  
    printf("[-] Set timeout:2.\n");
    setTimeout(s,2);
    printf("[-] Sending to server.\n");
    send(s,buf,sizeof(buf),0);
    memset(buf,0,sizeof(buf));
    printf("[-] Receving from server.\n");
    recv(s,buf,sizeof(buf),0);
    printf("[*] Recevie success!\n");
    printf("[*] HttpResponseMessage:\n--------------\n%s\n--------------\n",buf);
    closeSocket(s);
    printf("[-] Clsoe socket.\n");
    return 0;
}