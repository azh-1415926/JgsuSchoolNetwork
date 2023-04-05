#include "myhttp.h"
#define ACCOUNT "?user_account=%2C0%2C"
#define PASSWORD "&user_password="
static char account[11];
static char passwd[21];
void getUserInfo(char* buf){
    memset(account,0,sizeof(account));
    memset(passwd,0,sizeof(passwd));
    #if _WIN32
        FILE* f=fopen("passwd.txt","r");
        if(f==NULL){
            f=fopen("passwd.txt","w+");
            printf("Please enter your account[10]:");
            scanf("%10c",account);
            fflush(stdin);
            printf("Please enter your passwd[*]:");
            scanf("%s",passwd);
            fflush(stdin);
            fwrite(account,strlen(account),1,f);
            fwrite(passwd,strlen(passwd),1,f);
        }else{
            fread(account,10,1,f);
            fread(passwd,sizeof(passwd),1,f);
        }
        fclose(f);
    #elif __linux__
        int fd;
        if((fd=open("passwd.txt",O_RDONLY))>0){
            int ret=read(fd,account,10);
            if(ret<10){
                close(fd);
                perror("Account error!");
                exit(-1);
            }
            read(fd,passwd,sizeof(passwd));
        }else{
            fd=open("passwd.txt",O_RDWR|O_CREAT,777);
            printf("please input account(10):");
            scanf("%10c",account);
            printf("please input password(-)");
            scanf("%s",passwd);
            int count=write(fd,account,10);
            if(count<10){
                close(fd);
                unlink("passwd.txt");
                perror("Account error!");
                exit(-1);
            }
            write(fd,passwd,strlen(passwd));
        }
        close(fd);
    #endif
    strcat(buf,ACCOUNT);
    strcat(buf,account);
    strcat(buf,PASSWORD);
    strcat(buf,passwd);
}
void httpMessageInitalize(struct httpMessage* pMessage,int size,const char* method,const char* url,const char* version,const char* host){
    if(pMessage==NULL){
        printf("httpMessage is null,intitalize error!\n");
        return;
    }
    memset(pMessage,0,size);
    pMessage->method=(char*)method;
    pMessage->url=(char*)url;
    pMessage->version=(char*)version;
    pMessage->pField=(struct field_name*)malloc(sizeof(struct field_name));
    pMessage->pField->key="Host";
    pMessage->pField->value=(char*)host;
    pMessage->pField->next=NULL;
}
void httpMessageFree(struct httpMessage* pMessage){
    if(pMessage==NULL){
        printf("httpMessage is null,free error!\n");
        return;
    }
    struct field_name* pField=pMessage->pField;
    struct field_name* pTemp=NULL;
    while(pField->next){
        pTemp=pField;
        pField=pField->next;
        free(pTemp);
    }
    free(pField);
}
void httpMessageAddField(struct httpMessage* pMessage,const char*key,const char*value){
    if(pMessage==NULL){
        printf("httpMessage is null,addField error!\n");
        return;
    }
    struct field_name* pField=pMessage->pField;
    while(pField->next){
        pField=pField->next;
    }
    pField->next=(struct field_name*)malloc(sizeof(struct field_name));
    pMessage->pField->key=(char*)key;
    pMessage->pField->value=(char*)value;
    pMessage->pField->next=NULL;
}
void createHttpMessage(char *buf,struct httpMessage* pMessage){
    if(pMessage==NULL){
        printf("httpMessage is null,create error!\n");
        return;
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
}