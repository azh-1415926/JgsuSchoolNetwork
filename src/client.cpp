#include <mySocket/socket.hpp>
#include <myProtocol/httpMessage.hpp>
/* 测试，添加 cJSON 库 */
#include <cJSON.h>

#include "myInfo.h"

/* 提前定义服务端信息 */
#define SERVER_IP "192.168.167.42"
#define SERVER_PORT 801
#define HOST "192.168.167.42:801"
#define URL "/eportal/portal/login"

int main()
{
    try
    {
        /* 创建客户端套接字对象 socket */
        azh::ClientSocket socket;
        /* 创建 server_addr 结构体存储服务端的 ip、port 等信息 */
        struct sockaddr_in server_addr;
        /* 创建套接字地址对象，存储服务器套接字地址信息 */
        azh::SocketAddr serverAddr(AF_INET,SERVER_IP,SERVER_PORT);
        socket.setServerAddr(serverAddr);
        /* 打印服务端 ip、port */
        printf("[*] SERVER_IP:%s\n[*] SERVER_PORT:%d\n",SERVER_IP,SERVER_PORT);

        /* url 为请求的资源 */
        char url[512];
        /* 清空 url，并拼接用户信息 */
        memset(url,0,sizeof(url));
        strcat(url,URL);
        insertUserInfo(url);

        /* message 为报文对象 */
        azh::httpMessage message("GET",url);
        message.setHost(SERVER_IP);
        message.setPort(SERVER_PORT);
        std::string str=message.createMessage();
        /* 显示请求报文 */
        std::cout<<"[*] HttpRequestMessage:\n--------------\n"
            <<str<<"\n--------------\n";

        /* 连接到服务器 */
        std::cout<<"[-] Connecting to SERVER...\n";
        socket.Connect(); 
        /* 设置超时时长 */
        std::cout<<"[-] Set timeout:2.\n";
        socket.setTimeout(2);
        /* 发送请求报文 */
        std::cout<<"[-] Sending to server.\n";
        socket.Send(str);
        /* 接收响应报文 */
        std::cout<<"[-] Receving from server.\n";
        str=socket.Recv();
        socket.Close();
        std::cout<<"[*] Recevie success!\n";
        std::cout<<"[-] Clsoe socket.\n";
        /* 打印响应报文 */
        std::cout<<"[*] HttpResponseMessage:\n--------------\n"<<str<<"\n--------------\n";
    }
    catch(std::string error)
    {
        std::cout<<error;
    }
    return 0;
}