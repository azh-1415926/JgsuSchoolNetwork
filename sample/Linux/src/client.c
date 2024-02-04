#include "mysocket.h"
#include "myhttp.h"

#define SERVER_IP "192.168.167.42"
#define SERVER_PORT 801
#define HOST "192.168.167.42:801"
#define URL "/eportal/portal/login"

#define ACCOUNT "?user_account=%2C0%2C"
#define PASSWORD "&user_password="

void getUserInfo(char* buf)
{
    int fd;
    char account[11];
    char password[21];
    memset(account,0,sizeof(account));
    memset(password,0,sizeof(password));
    if((fd=open("passwd.txt",O_RDONLY))>0)
    {
        int ret=read(fd,account,10);
        if(ret<10)
        {
            close(fd);
            perror("Account error!");
            exit(-1);
        }
        read(fd,password,sizeof(password));
    }
    else
    {
        fd=open("passwd.txt",O_RDWR|O_CREAT,777);
        printf("please input account(10):");
        scanf("%10c",account);
        printf("please input password(-)");
        scanf("%s",password);
        int count=write(fd,account,10);
        if(count<10)
        {
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

int main()
{
    /*
        fd 为客户端套接字的文件描述符
        buf 读取或发送到服务端的文本缓冲,url 为请求的地址
        server_addr 为服务端套接字地址信息
    */
    int fd;
    char buf[512],url[512];
    struct sockaddr_in server_addr;

    /* 设置服务端的套接字地址信息 */
    memset(&server_addr,0,sizeof(server_addr));
    setSockaddr(&server_addr,AF_INET,SERVER_IP,SERVER_PORT);
    printf("[*] SERVER_IP:%s\n[*] SERVER_PORT:%d\n",SERVER_IP,SERVER_PORT);

    /* 读取用户信息，拼接到 url */
    memset(url,0,sizeof(url));
    strcat(url,URL);
    getUserInfo(url);

    /* 创建 http 报文 */
    struct httpMessage http;
    httpMessageInitalize(&http,sizeof(http),"GET",url,"HTTP/1.1",HOST);
    memset(buf,0,sizeof(buf));
    createHttpMessage(buf,&http);
    httpMessageFree(&http);
    printf("[*] HttpRequestMessage:\n--------------\n%s\n--------------\n",buf);

    /* 创建套接字并连接到服务器 */
    fd=Socket(AF_INET,SOCK_STREAM,0);
    printf("[-] Connecting to SERVER..., Set NonBlock.\n");
    Connect(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));

    /* 设置超时时长 */
    printf("[-] Set send and receive timeout:2.\n");
    SetSendTimeOut(fd,2);
    SetReceiveTimeOut(fd,2);

    /* 发送请求报文 */
    printf("[-] Sending HttpRequestMessage...\n");
    Send(fd,buf,sizeof(buf),0);

    /* 接收响应报文 */
    printf("[-] Receiving HttpRespnseMessage...\n");
    memset(buf,0,sizeof(buf));
    Recv(fd,buf,sizeof(buf),0);

    /* 打印响应报文并关闭套接字 */
    printf("[*] HttpResponseMessage:\n--------------\n%s\n--------------\n",buf);
    Close(fd);
    printf("[-] Close Socket.\n");
    return 0;
}