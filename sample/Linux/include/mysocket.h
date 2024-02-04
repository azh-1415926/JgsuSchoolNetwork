#ifndef _MY_SOCKET_H_
#define _MY_SOCKET_H_

/* 通用头文件 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* 网络库头文件 */
#include<sys/socket.h>
#include<arpa/inet.h>

/* 系统调用头文件 */
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

/* 处理错误 */
void myError(const char *err);

/* 生成套接字地址信息 */
struct sockaddr_in* setSockaddr(struct sockaddr_in* server_addr,int af,const char* server_ip,int server_port);
/* 创建套接字，返回文件描述符 */
int Socket(int domain,int type,int protocol);
/* 连接到服务器(客户端) */
int Connect(int fd,struct sockaddr* server_addr,socklen_t server_len);
/* 设置发送超时时长 */
int SetSendTimeOut(int fd,int time);
/* 设置接收超时时长 */
int SetReceiveTimeOut(int fd,int time);
/* 往套接字里写数据 */
int Send(int fd,const char *buf,int size,int flag);
/* 从套接字里读数据 */
int Recv(int fd,char *buf,int size,int flag);
/* 关闭套接字 */
int Close(int fd);

#endif