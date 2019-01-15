#include "tcpnetwork.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

TcpNetwork *TcpNetwork::m_self = NULL;

TcpNetwork::TcpNetwork()
{
}

/*  返回用于监听的文件描述符
  */
int TcpNetwork::getSockfd() const
{
    std::cout << m_sockfd << std::endl;

    return m_sockfd;
}

/*  对socket函数出错处理，创建网络通信描述符
    参数family指定为IPv4
        type指定是字节流（TCP）还是文本流（UDP)
        protocol默认为0
    返回网络通信描述符
*/
int TcpNetwork::mySocket(int family, int type, int protocol)
{
    int sockfd;

    //返回-1说明socket出错，此时终止进程
    if ((sockfd = socket(family, type, protocol)) < 0 )
    {
        //输出错误原因
        perror("socket error:");
        exit(1);
    }

    return sockfd;
}

/*  对bind函数出错处理，将网络通信描述符和服务器IP，端口绑定
    参数sockfd网络通信描述符
        servaddr服务器地址（IP和端口号）
        servaddr_len服务器地址字节数
*/
void TcpNetwork::myBind(int sockfd, const struct sockaddr *serverAddr,
             socklen_t servAddrLen)
{
    int n = 0;

     //返回-1说明bind出错，此时终止进程
    if ((n = bind(sockfd, serverAddr, servAddrLen)) < 0)
    {
        perror("bind error");
        exit(1);
    }
}

/*  对listen函数出错处理，设置监听和最大允许客户连接数
    参数sockfd网络通信描述符
        backlog最大允许客户连接数
*/
void TcpNetwork::myListen(int sockfd, int backlog)
{
    int n = 0;

    //返回-1说明listen出错，此时终止进程
    if ((n = listen(sockfd, backlog)) < 0)
    {
        perror("listen error");
        exit(1);
    }
}

/*  初始化网络
  */
void TcpNetwork::initNetwork()
{
    struct sockaddr_in serverAddr;
    int opt = 1;

    //创建一个文件描述符，用来监听里连接
    m_sockfd = mySocket(AF_INET, SOCK_STREAM, 0);

    //初始化服务器地址和端口号
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    //htonl将主机IP地址转化为网络可用格式
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //htons将主机端口号转化为网络可用格式
    serverAddr.sin_port = htons(SERV_PORT);

    //设置允许关闭后立即启动
    setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    //将网络端口和服务器地址绑定
    myBind(m_sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    //设置监听和最大允许客户连接数
    myListen(m_sockfd, FD_SETSIZE);

    std::cout << m_sockfd << std::endl;
}

