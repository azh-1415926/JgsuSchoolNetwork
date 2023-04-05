#include "mysocket.h"
#include "myhttp.h"
#define SERVER_IP "192.168.167.42"
#define SERVER_PORT 801
#define HOST "192.168.167.42:801"
#define URL "/eportal/portal/login"
int main(){
    int fd;
    char buf[512];
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    setSockaddr(&server_addr,AF_INET,SERVER_IP,SERVER_PORT);
    printf("[*] SERVER_IP:%s\n[*] SERVER_PORT:%d\n",SERVER_IP,SERVER_PORT);
    struct httpMessage http;
    httpMessageInitalize(&http,sizeof(http),"GET",URL,"HTTP/1.1",HOST);
    createHttpMessage(buf,&http);
    httpMessageFree(&http);
    printf("[*] HttpRequestMessage:\n--------------\n%s\n--------------\n",buf);
    fd=Socket(AF_INET,SOCK_STREAM,0);
    printf("[-] Connecting to SERVER..., Set NonBlock.\n");
    Connect(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf("[-] Set send and receive timeout:2.\n");
    SetSendTimeOut(fd,2);
    SetReceiveTimeOut(fd,2);
    printf("[-] Sending HttpRequestMessage...\n");
    Send(fd,buf,sizeof(buf),0);
    memset(buf,0,sizeof(buf));
    printf("[-] Receiving HttpRespnseMessage...\n");
    Recv(fd,buf,sizeof(buf),0);
    printf("[*] HttpResponseMessage:\n--------------\n%s\n--------------\n",buf);
    Close(fd);
    printf("[-] Close Socket.\n");
    return 0;
}