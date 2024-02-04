#ifndef _MY_SOCKET_H_
#define _MY_SOCKET_H_

/* 通用头文件 */
#include <stdio.h>
#include <stdbool.h>

/* 网络编程头文件和依赖库 */
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

/* 初始化套接字地址信息 */
void initalizeSockaddr_in(struct sockaddr_in* server_addr,int af,const char* ip,int port);
/* 初始化套接字 */
bool initalizeSocket();
/* 创建套接字 */
SOCKET Socket(int af,int type,int protocol);
/* 连接到服务端(客户端函数) */
void Connect(SOCKET s,struct sockaddr* server_addr,int len);
/* 设置超时时长 */
void setTimeout(SOCKET s,int time);
/* 关闭套接字 */
void closeSocket(SOCKET s);

#endif