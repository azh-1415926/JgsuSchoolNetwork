#include "mysocket.h"
#include "myhttp.h"

/* 测试，添加 cJSON 库 */
#include <cJSON.h>

/* 提前定义服务端信息 */
#define SERVER_IP "192.168.167.42"
#define SERVER_PORT 801
#define HOST "192.168.167.42:801"
#define URL "/eportal/portal/login"

int main()
{
    /* 套接字描述符 s，buf 用于存储请求报文或响应报文 */
    SOCKET_FD s;
    char buf[512];
    /* server_addr 结构体存储服务端的 ip、port 等信息 */
    struct sockaddr_in server_addr;
    /* 初始化 server_addr */
    setSockaddr(&server_addr,sizeof(server_addr),AF_INET,SERVER_IP,SERVER_PORT);
    /* 打印服务端 ip、port */
    printf("[*] SERVER_IP:%s\n[*] SERVER_PORT:%d\n",SERVER_IP,SERVER_PORT);
    #if _WIN32
        /* 正确显示中文 */
        system("chcp 65001");
        /* Windows 平台需要初始化套接字 */
        printf("[-] Winsock Initalize.\n");
        initalizeSocket();
    #endif
    /* http 为请求报文 */
    struct http_message http;
    /* 初始化报文，设置请求方式、url、http 版本 */
    httpMessageInitalize(&http,sizeof(http),"GET",URL,"HTTP/1.1",HOST);
    /* 清空 buf */
    memset(buf,0,sizeof(buf));
    /* 用 buf 接收 http 创建的报文 */
    createHttpMessage(buf,&http);
    /* 释放报文 */
    httpMessageFree(&http);
    /* 显示请求报文 */
    printf("[*] HttpRequestMessage:\n--------------\n%s\n--------------\n",buf);
    /* 创建套接字 */
    s=Socket(AF_INET,SOCK_STREAM,0);
    /* 连接到服务器 */
    printf("[-] Connecting to SERVER...\n");
    Connect(s,(struct sockaddr*)&server_addr,sizeof(server_addr)); 
    /* 设置超时时长 */
    printf("[-] Set timeout:2.\n");
    setTimeout(s,2);
    /* 发送请求报文 */
    printf("[-] Sending to server.\n");
    send(s,buf,sizeof(buf),0);
    /* 清空 buf 用于接收返回的响应报文 */
    memset(buf,0,sizeof(buf));
    printf("[-] Receving from server.\n");
    recv(s,buf,sizeof(buf),0);
    printf("[*] Recevie success!\n");
    /* 打印响应报文 */
    printf("[*] HttpResponseMessage:\n--------------\n%s\n--------------\n",buf);
    /* 关闭套接字 */
    closeSocket(s);
    printf("[-] Clsoe socket.\n");
    return 0;
}