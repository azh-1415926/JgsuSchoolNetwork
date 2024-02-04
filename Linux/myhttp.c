#include "myhttp.h"

/* 系统编程头文件 */
#include<unistd.h>
#include<fcntl.h>

int httpMessageInitalize(struct httpMessage* pMessage,int size,const char* method,const char* url,const char* version,const char* host)
{
    if(pMessage==NULL)
    {
        printf("httpMessage is null,intitalize error!\n");
        return -1;
    }
    memset(pMessage,0,size);
    pMessage->method=(char*)method;
    pMessage->url=(char*)url;
    pMessage->version=(char*)version;
    pMessage->pField=(struct field_name*)malloc(sizeof(struct field_name));
    pMessage->pField->key="Host";
    pMessage->pField->value=(char*)host;
    pMessage->pField->next=NULL;
    return 0;
}

int httpMessageAddField(struct httpMessage* pMessage,const char*key,const char*value)
{
    if(pMessage==NULL)
    {
        printf("httpMessage is null,addField error!\n");
        return -1;
    }
    struct field_name* pField=pMessage->pField;
    while(pField->next)
    {
        pField=pField->next;
    }
    pField->next=(struct field_name*)malloc(sizeof(struct field_name));
    pMessage->pField->key=(char*)key;
    pMessage->pField->value=(char*)value;
    pMessage->pField->next=NULL;
    return 0;
}
int httpMessageFree(struct httpMessage* pMessage){
    if(pMessage==NULL)
    {
        printf("httpMessage is null,free error!\n");
        return -1;
    }
    struct field_name* pField=pMessage->pField;
    struct field_name* pTemp=NULL;
    while(pField->next)
    {
        pTemp=pField;
        pField=pField->next;
        free(pTemp);
    }
    free(pField);
    return 0;
}
int createHttpMessage(char *buf,struct httpMessage* pMessage)
{
    if(pMessage==NULL)
    {
        printf("httpMessage is null,create error!\n");
        return -1;
    }
    strcat(buf, pMessage->method);
    strcat(buf, " ");
    strcat(buf, pMessage->url);
    strcat(buf, " ");
    strcat(buf, pMessage->version);
    strcat(buf, "\n");
    struct field_name* pField=pMessage->pField;
    do
    {
        strcat(buf, pField->key);
        strcat(buf,":");
        strcat(buf, pField->value);
        strcat(buf, "\n");
        if(pField->next)
            pField=pField->next;
        else
            pField=NULL;
    }
    while(pField);
    strcat(buf, "\r\n");
    return 0;
}
