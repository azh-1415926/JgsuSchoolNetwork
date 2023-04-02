#ifndef _MY_HTTP_H_
#define _MY_HTTP_H_
#include<stdio.h>
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
int httpMessageInitalize(struct httpMessage* pMessage,int size,const char* method,const char* url,const char* version,const char* host);
int httpMessageAddField(struct httpMessage* pMessage,const char*key,const char*value);
int httpMessageFree(struct httpMessage* pMessage);
int createHttpMessage(char *buf,struct httpMessage* pMessage);
#endif