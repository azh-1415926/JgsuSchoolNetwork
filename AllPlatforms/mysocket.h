#ifndef _MY_SOCKET_H_
#define _MY_SOCKET_H_
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#if _WIN32
#include <winsock2.h>
#include<ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
typedef SOCKET SOCKET_FD;
bool initalizeSocket();
#elif __linux__
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
typedef int SOCKET_FD;
#endif
struct sockaddr_in* setSockaddr(struct sockaddr_in* server_addr,int af,const char* server_ip,int server_port);
SOCKET_FD Socket(int af,int type,int protocol);
bool Connect(SOCKET_FD s,struct sockaddr* server_addr,socklen_t server_len);
void setTimeout(SOCKET_FD s,int time);
void closeSocket(SOCKET_FD s);
#endif
