#ifndef CONNECTEVENT_H
#define CONNECTEVENT_H

#include <sys/socket.h>

class ConnectEvent
{
public:
    ConnectEvent();

    int getConnfd() const;

    void connectClient(int sockfd);

private:
    int m_connfd;

    int myAccept(int sockfd, struct sockaddr *clientAddr,
                  socklen_t *clientAddrLen);
};

#endif // CONNECTEVENT_H
