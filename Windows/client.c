#include "mysocket.h"
#include "myhttp.h"
#include <stdio.h>
#define SERVER_IP "192.168.167.42"
#define SERVER_PORT 801
int main(){
    SOCKET s;
    struct sockaddr_in server_addr;
    char buf[512];
    char response[1024];
    const char* key[1]={"Host"};
    const char* value[1]={"192.168.167.42:801"};
    getUserInfo();
    createHttpRequest(buf,sizeof(buf),"GET","/eportal/portal/login",1,key,value);
    printf("%s\n",buf);
    initalizeSockaddr_in(&server_addr,AF_INET,SERVER_IP,SERVER_PORT);
    printf("[-] Winsock Initalize.\n");
    initalizeSocket();
    s=Socket(AF_INET,SOCK_STREAM,0);
    printf("[-] Connectting to server.\n");
    Connect(s,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf("[*] Set send and recv timeout:2s.\n");
    setTimeout(s,2);
    printf("[-] Sending to server.\n");
    send(s,buf,sizeof(buf),0);
    printf("[-] Receving from server.\n");
    recv(s,response,sizeof(response),0);
    printf("[*] Recevie success!\n");
    printf("%s\n",response);
    closeSocket(s);
    printf("[-] Clsoe socket.\n");
    return 0;
}