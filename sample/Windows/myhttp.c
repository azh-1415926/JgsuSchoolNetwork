#include "myhttp.h"
#include <stdlib.h>
#include <string.h>

static char account[11];
static char passwd[21];

void getUserInfo()
{
    memset(account,0,sizeof(account));
    memset(passwd,0,sizeof(passwd));
    FILE* f=fopen("passwd.txt","r");
    if(f==NULL)
    {
        f=fopen("passwd.txt","w+");
        printf("Please enter your account[10]:");
        scanf("%10c",account);
        fflush(stdin);
        printf("Please enter your passwd[*]:");
        scanf("%s",passwd);
        fflush(stdin);
        fwrite(account,strlen(account),1,f);
        fwrite(passwd,strlen(passwd),1,f);
    }
    else
    {
        fread(account,10,1,f);
        fread(passwd,sizeof(passwd),1,f);
    }
}

void createHttpRequest(char* buf,int size,const char* method,const char* url,int argc,const char** key,const char** value)
{
    memset(buf,0,size);
    strcat(buf,method);
    strcat(buf," ");
    strcat(buf,url);
    strcat(buf,"?user_account=%2C0%2C");
    strcat(buf,account);
    strcat(buf,"&user_password=");
    strcat(buf,passwd);
    strcat(buf," HTTP/1.1\n");
    for(int i=0;i<argc;i++)
    {
        strcat(buf,key[i]);
        strcat(buf,":");
        strcat(buf,value[i]);
        strcat(buf,"\n");
    }
    strcat(buf,"\n");
}