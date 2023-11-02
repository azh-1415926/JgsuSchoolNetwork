#ifndef _MY_SOCKET_H_
#define _MY_SOCKET_H_

/* 通用头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#if _WIN32

/* Windows 平台所需头文件 */
#include <winsock2.h>
#include<ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

/* 用 SOCKET_FD 代替 SOCKET，统一类型名 */
typedef SOCKET SOCKET_FD;
/* Windows 平台下还需要初始化套接字，额外定义一个函数 */
bool initalizeSocket();

#elif __linux__

/* Linux 平台所需头文件 */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* 用 SOCKET_FD 代替 int，统一类型名 */
typedef int SOCKET_FD;

#endif

struct sockaddr_in* setSockaddr(struct sockaddr_in* server_addr,unsigned int size,int af,const char* server_ip,unsigned int server_port);
SOCKET_FD Socket(int af,int type,int protocol);
bool Connect(SOCKET_FD s,struct sockaddr* server_addr,socklen_t server_len);
void setTimeout(SOCKET_FD s,int time);
void closeSocket(SOCKET_FD s);

#endif