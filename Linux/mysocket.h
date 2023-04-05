#ifndef _MY_SOCKET_H_
#define _MY_SOCKET_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
void myError(const char *err);
struct sockaddr_in* setSockaddr(struct sockaddr_in* server_addr,int af,const char* server_ip,int server_port);
int Socket(int domain,int type,int protocol);
int Connect(int fd,struct sockaddr* server_addr,socklen_t server_len);
int SetSendTimeOut(int fd,int time);
int SetReceiveTimeOut(int fd,int time);
int Send(int fd,const char *buf,int size,int flag);
int Recv(int fd,char *buf,int size,int flag);
int Close(int fd);
#endif