#include "myhttp.h"

#if __linux__

/* Linux 平台所用系统调用的头文件 */
#include<fcntl.h>
#include<unistd.h>

#endif

#define ACCOUNT "?user_account=%2C0%2C"
#define PASSWORD "&user_password="

/* acount 用于存储学号、passwd 存储密码，多一位字符用于存储 '\0' */
static char account[11];
static char passwd[21];

/* 获取用户账号、密码，填充到 buf 中 */
void getUserInfo(char* buf)
{
    /* 清空 acount、passwd */
    memset(account,0,sizeof(account));
    memset(passwd,0,sizeof(passwd));
    /* Windows 用库函数读取 passwd.txt 文件 */
    #if _WIN32
        /* 只读方式打开文件 */
        FILE* f=fopen("passwd.txt","r");
        /* f 为空即 passwd.txt 文件不存在 */
        if(f==NULL)
        {
            /* 没有便创建一个 passwd.txt */
            f=fopen("passwd.txt","w+");
            /* 读取用户输入的 10 位的学号 */
            printf("Please enter your account[10]:");
            scanf("%10c",account);
            /* 读走缓冲区剩余字符 */
            scanf("%*s");
            /* 读取用户输入的密码 */
            printf("Please enter your passwd[*]:");
            scanf("%s",passwd);
            /* 将 acount、passwd 写入文件中 */
            fwrite(account,strlen(account),1,f);
            fwrite(passwd,strlen(passwd),1,f);
        }
        /* f 不为空即 passwd.txt 文件存在，读取文件中的学号、密码 */
        else
        {
            fread(account,10,1,f);
            fread(passwd,sizeof(passwd),1,f);
        }
        /* 关闭文件 */
        fclose(f);
    #elif __linux__
        /* fd 为读取或写入 passwd.txt 文件的描述符 */
        int fd;
        /* fd 大于 0，即 passwd.txt 文件存在 */
        if((fd=open("passwd.txt",O_RDONLY))>0)
        {
            /* 读取前十个字符作为学号 */
            int ret=read(fd,account,10);
            /* 若字符不足 10 位，报错退出 */
            if(ret<10)
            {
                close(fd);
                perror("Account error!");
                exit(-1);
            }
            /* 剩余字符作为密码 */
            read(fd,passwd,sizeof(passwd));
        }
        /* fd 小于等于 0，即 passwd.txt 文件不存在 */
        else
        {
            /* 以读写方式打开 passwd.txt 文件，没有便创建，权限为 0777 */
            fd=open("passwd.txt",O_RDWR|O_CREAT,777);
            /* 读取用户输入的 10 位的学号 */
            printf("please input account(10):");
            scanf("%10c",account);
            /* 读走缓冲区剩余字符 */
            scanf("%*s");
            /* 读取用户输入的密码 */
            printf("please input password(-)");
            scanf("%s",passwd);
            /* 将 account 写入文件中，若不足 10 位，删除文件，报错退出 */
            int count=write(fd,account,10);
            if(count<10)
            {
                close(fd);
                unlink("passwd.txt");
                perror("Account error!");
                exit(-1);
            }
            /* 将 passwd 写入文件中 */
            write(fd,passwd,strlen(passwd));
        }
        /* 关闭文件 */
        close(fd);
    #endif
    /* 拼接学号参数名、学号，密码参数名、密码 */
    strcat(buf,ACCOUNT);
    strcat(buf,account);
    strcat(buf,PASSWORD);
    strcat(buf,passwd);
}

/* 初始化报文，根据传入的请求方式、url、http 版本、host 初始化 */
void httpMessageInitalize(struct httpMessage* pMessage,int size,const char* method,const char* url,const char* version,const char* host)
{
    /* 若报文指针为空，直接返回 */
    if(pMessage==NULL)
    {
        printf("httpMessage is null,intitalize error!\n");
        return;
    }
    /* 清空报文 */
    memset(pMessage,0,size);
    /* 插入报文头 */
    pMessage->method=(char*)method;
    pMessage->url=(char*)url;
    pMessage->version=(char*)version;
    /* 插入 Host 字段 */
    pMessage->pField=(struct field_name*)malloc(sizeof(struct field_name));
    pMessage->pField->key="Host";
    pMessage->pField->value=(char*)host;
    pMessage->pField->next=NULL;
}

/* 释放报文 */
void httpMessageFree(struct httpMessage* pMessage)
{
    /* 若报文指针为空，直接返回 */
    if(pMessage==NULL)
    {
        printf("httpMessage is null,free error!\n");
        return;
    }
    /* pField 指向字段，pTemp 指向需要释放的字段 */
    struct field_name* pField=pMessage->pField;
    struct field_name* pTemp=NULL;
    while(pField->next)
    {
        pTemp=pField;
        pField=pField->next;
        free(pTemp);
    }
    free(pField);
}

/* 为报文中添加字段，根据传入的 key、value 添加 */
void httpMessageAddField(struct httpMessage* pMessage,const char*key,const char*value)
{
    /* 若报文指针为空，直接返回 */
    if(pMessage==NULL)
    {
        printf("httpMessage is null,addField error!\n");
        return;
    }
    /* pField 指向字段 */
    struct field_name* pField=pMessage->pField;
    /* 遍历到最后一个字段 */
    while(pField->next)
        pField=pField->next;
    /* 在最后一个字段插入新字段 */
    pField->next=(struct field_name*)malloc(sizeof(struct field_name));
    pMessage->pField->key=(char*)key;
    pMessage->pField->value=(char*)value;
    pMessage->pField->next=NULL;
}

/* 创建报文 */
void createHttpMessage(char *buf,struct httpMessage* pMessage)
{
    /* 若报文指针为空，直接返回 */
    if(pMessage==NULL)
    {
        printf("httpMessage is null,create error!\n");
        return;
    }
    /* 插入报文头到 buf */
    strcat(buf, pMessage->method);
    strcat(buf, " ");
    strcat(buf, pMessage->url);
    getUserInfo(buf);
    strcat(buf, " ");
    strcat(buf, pMessage->version);
    strcat(buf, "\n");
    /* 插入字段到 buf */
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
}