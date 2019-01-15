#include "network.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

Network *Network::m_self = NULL;

Network::Network()
{
}

/*  返回通信的文件描述符
  */
int Network::getConnfd() const
{
    std::cout << m_connfd << std::endl;
    return m_connfd;
}

/*  对socket函数出错处理，创建网络通信描述符
    参数family指定为IPv4
        type指定是字节流（TCP）还是文本流（UDP)
        protocol默认为0
    返回网络通信描述符
*/
int Network::mySocket(int family, int type, int protocol)
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

/*  对connect函数出错处理，向服务器请求通信
    参数connfd为socket返回的网络通信描述符
        servaddr为服务器地址
        servaddrlen地址字节大小
*/
void Network::myConnect(int connfd, struct sockaddr *servaddr,
                int servaddrlen)
{
    int n;

    //返回-1说明connect出错，此时终止进程
    if ((n = connect(connfd, servaddr, servaddrlen)) < 0)
    {
        //输出错误原因
        perror("connect error:");
        exit(1);
    }
}

void Network::initNetwork()
{
    struct sockaddr_in serverAddr;

    //打开网络通信端
    m_connfd = mySocket(AF_INET, SOCK_STREAM, 0);

    //初始化服务器地址和端口号
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    //servaddr.sin_addr.s_addr = htonl("127.0.0.1");
    inet_pton(AF_INET, SERV_IP, &serverAddr.sin_addr);
    serverAddr.sin_port = htons(SERV_PORT);

    //申请连接服务器
    myConnect(m_connfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    std::cout << m_connfd << std::endl;
}
