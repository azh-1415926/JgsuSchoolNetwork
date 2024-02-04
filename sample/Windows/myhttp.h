#ifndef _MY_HTTP_H_
#define _MY_HTTP_H_

/* 通用头文件 */
#include <stdio.h>

/* 获取用户信息 */
void getUserInfo();
/* 创建报文信息 */
void createHttpRequest(char* buf,int size,const char* method,const char* url,int argc,const char** keys,const char** values);

#endif