#ifndef _MY_HTTP_H_
#define _MY_HTTP_H_
#include <stdio.h>
void getUserInfo();
void createHttpRequest(char* buf,int size,const char* method,const char* url,int argc,const char** key,const char** value);
#endif