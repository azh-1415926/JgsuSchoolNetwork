#include "myhttp.h"
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define ACCOUNT "?user_account=%2C0%2C"
#define PASSWORD "&user_password="
void getUserInfo(char* buf){
    int fd;
    char account[11];
    char password[21];
    memset(account,0,sizeof(account));
    memset(password,0,sizeof(password));
    if((fd=open("passwd.txt",O_RDONLY))>0){
        int ret=read(fd,account,10);
        if(ret<10){
            close(fd);
            perror("Account error!");
            exit(-1);
        }
        read(fd,password,sizeof(password));
    }else{
        fd=open("passwd.txt",O_RDWR|O_CREAT,777);
        printf("please input account(10):");
        scanf("%10c",account);
        printf("please input password(-)");
        scanf("%s",password);
        int count=write(fd,account,10);
        if(count<10){
            close(fd);
            unlink("passwd.txt");
            perror("Account error!");
            exit(-1);
        }
        write(fd,password,strlen(password));
    }
    strcat(buf,ACCOUNT);
    strcat(buf,account);
    strcat(buf,PASSWORD);
    strcat(buf,password);
    close(fd);
}
int httpMessageInitalize(struct httpMessage* pMessage,int size,const char* method,const char* url,const char* version,const char* host){
    if(pMessage==NULL){
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
int httpMessageAddField(struct httpMessage* pMessage,const char*key,const char*value){
    if(pMessage==NULL){
        printf("httpMessage is null,addField error!\n");
        return -1;
    }
    struct field_name* pField=pMessage->pField;
    while(pField->next){
        pField=pField->next;
    }
    pField->next=(struct field_name*)malloc(sizeof(struct field_name));
    pMessage->pField->key=(char*)key;
    pMessage->pField->value=(char*)value;
    pMessage->pField->next=NULL;
    return 0;
}
int httpMessageFree(struct httpMessage* pMessage){
    if(pMessage==NULL){
        printf("httpMessage is null,free error!\n");
        return -1;
    }
    struct field_name* pField=pMessage->pField;
    struct field_name* pTemp=NULL;
    while(pField->next){
        pTemp=pField;
        pField=pField->next;
        free(pTemp);
    }
    free(pField);
    return 0;
}
int createHttpMessage(char *buf,struct httpMessage* pMessage){
    if(pMessage==NULL){
        printf("httpMessage is null,create error!\n");
        return -1;
    }
    strcat(buf, pMessage->method);
    strcat(buf, " ");
    strcat(buf, pMessage->url);
    getUserInfo(buf);
    strcat(buf, " ");
    strcat(buf, pMessage->version);
    strcat(buf, "\n");
    struct field_name* pField=pMessage->pField;
    do{
        strcat(buf, pField->key);
        strcat(buf,":");
        strcat(buf, pField->value);
        strcat(buf, "\n");
        if(pField->next){
            pField=pField->next;
        }else{
            pField=NULL;
        }
    }while(pField);
    strcat(buf, "\r\n");
    return 0;
}
