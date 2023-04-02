#ifndef _MY_HTTP_H_
#define _MY_HTTP_H_
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#if _WIN32
#elif __linux__
#include<fcntl.h>
#include<unistd.h>
#endif
struct field_name {
    char* key;
    char* value;
    struct field_name* next;
};
struct httpMessage {
    char* method;
    char* url;
    char* version;
    struct field_name* pField;
};
void getUserInfo(char* buf);
void httpMessageInitalize(struct httpMessage* pMessage,int size,const char* method,const char* url,const char* version,const char* host);
void httpMessageFree(struct httpMessage* pMessage);
void httpMessageAddField(struct httpMessage* pMessage,const char*key,const char*value);
void createHttpMessage(char *buf,struct httpMessage* pMessage);
#endif
