#ifndef _MY_HTTP_H_
#define _MY_HTTP_H_

/* field_name 为字段 */
struct field_name
{
    char* key;
    char* value;
    struct field_name* next;
};
/* http_message 为 http 报文 */
struct http_message
{
    char* method;
    char* url;
    char* version;
    struct field_name* pField;
};

void getUserInfo(char* buf);
void httpMessageInitalize(struct http_message* pMessage,int size,const char* method,const char* url,const char* version,const char* host);
void httpMessageFree(struct http_message* pMessage);
void httpMessageAddField(struct http_message* pMessage,const char*key,const char*value);
void createHttpMessage(char *buf,struct http_message* pMessage);

#endif