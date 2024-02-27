#include "mysocket.h"
#include "myhttp.h"

#include <stdio.h>

#define SERVER_IP "192.168.77.18"
#define SERVER_PORT 801

int main()
{
    /*
        s 为套接字
        server_addr 为服务端套接字地址信息
        request 为请求报文
        response 为响应报文
    */
    SOCKET s;
    struct sockaddr_in server_addr;
    char request[512];
    char response[1024];

    /*
        keys、values 为所有字段的关键字、值的集合
    */
    const char* keys[]={"Host"};
    const char* values[]={"192.168.167.42:801"};

    /* 获取用户信息 */
    getUserInfo();

    /* 创建请求报文，并打印 */
    createHttpRequest(request,sizeof(request),"GET","/eportal/portal/login",1,keys,values);
    printf("%s\n",request);

    /* 初始化套接字，并创建 */
    initalizeSockaddr_in(&server_addr,AF_INET,SERVER_IP,SERVER_PORT);
    printf("[-] Winsock Initalize.\n");
    initalizeSocket();
    s=Socket(AF_INET,SOCK_STREAM,0);

    /* 连接到服务端，并设置发送超时时长 */
    printf("[-] Connectting to server.\n");
    Connect(s,(struct sockaddr*)&server_addr,sizeof(server_addr));
    printf("[*] Set send and recv timeout:2s.\n");
    setTimeout(s,2);

    /* 发送请求报文 */
    printf("[-] Sending to server.\n");
    send(s,request,sizeof(request),0);

    /* 接收响应报文 */
    printf("[-] Receving from server.\n");
    recv(s,response,sizeof(response),0);
    printf("[*] Recevie success!\n");

    /* 打印响应报文并关闭套接字 */
    printf("%s\n",response);
    closeSocket(s);
    printf("[-] Clsoe socket.\n");
    return 0;
}