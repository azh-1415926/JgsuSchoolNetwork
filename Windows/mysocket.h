#ifndef _MY_SOCKET_H_
#define _MY_SOCKET_H_
#include <stdio.h>
#include <winsock2.h>
#include <stdbool.h>
#pragma comment(lib,"ws2_32.lib")
void initalizeSockaddr_in(struct sockaddr_in* server_addr,int af,const char* ip,int port);
bool initalizeSocket();
SOCKET Socket(int af,int type,int protocol);
void Connect(SOCKET s,struct sockaddr* server_addr,int len);
void setTimeout(SOCKET s,int time);
void closeSocket(SOCKET s);
#endif