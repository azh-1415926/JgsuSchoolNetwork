#ifndef _MY_HTTP_H_
#define _MY_HTTP_H_

/* 通用头文件 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct field_name
{
    char* key;
    char* value;
    struct field_name* next;
};

struct httpMessage
{
    char* method;
    char* url;
    char* version;
    struct field_name* pField;
};

/* 初始化 http 报文 */
int httpMessageInitalize(struct httpMessage* pMessage,int size,const char* method,const char* url,const char* version,const char* host);
/* 添加字段 */
int httpMessageAddField(struct httpMessage* pMessage,const char*key,const char*value);
/* 释放 http 报文 */
int httpMessageFree(struct httpMessage* pMessage);
/* 生成 http 报文 */
int createHttpMessage(char *buf,struct httpMessage* pMessage);

#endif