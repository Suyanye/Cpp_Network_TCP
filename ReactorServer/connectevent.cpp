#include "connectevent.h"

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>

ConnectEvent::ConnectEvent()
{
}

/*   返回和客户端通信的文件描述符
  */
int ConnectEvent::getConnfd() const
{
    std::cout << m_connfd << std::endl;

    return m_connfd;
}

/*  对accept函数出错处理，等待客户连接
    参数sockfd网络通信描述符
        cliaddr客户地址（IP和端口号）
        cliaddr_len客户地址字节数
    返回服务器和客户端的通信描述符
*/
int ConnectEvent::myAccept(int sockfd, struct sockaddr *clientAddr,
                           socklen_t *clientAddrLen)
{
    int n;

    //当accept返回-1且错误号为ECONNABORTED，EINTR时重新监听连接
    //否者accept出错打印错误原因并退出
again:
    if ( (n = accept(sockfd, clientAddr, clientAddrLen)) < 0)
    {
        if ((errno == ECONNABORTED) || (errno == EINTR))
        {
            goto again;
        }else
        {
            perror("accept error");
            exit(1);
        }
    }

    return n;
}

/*  连接客户端的请求
  */
void ConnectEvent::connectClient(int sockfd)
{
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = 0;

    clientAddrLen = sizeof(clientAddr);

    //阻塞等待客户连接
    m_connfd = myAccept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);

    std::cout << m_connfd << std::endl;
}
