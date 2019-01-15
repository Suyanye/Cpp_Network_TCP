#include <iostream>

#include "tcpnetwork.h"
#include "connectevent.h"

int main()
{
    int sockfd = 0;
    int connfd = 0;

    TcpNetwork::single()->initNetwork();

    sockfd = TcpNetwork::single()->getSockfd();

    std::cout << sockfd << std::endl;

    ConnectEvent *connectAccept = new ConnectEvent();

    connectAccept->connectClient(sockfd);

    connfd = connectAccept->getConnfd();

    std::cout << connfd << std::endl;

    return 0;
}

