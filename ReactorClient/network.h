#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <stdlib.h>

#define SERV_IP     "127.0.0.1"
#define SERV_PORT   6666

class Network
{
public:
    Network();

    int getConnfd() const;
    void initNetwork();

    static Network *single()
    {
        if (NULL == m_self)
        {
            m_self = new Network();
        }

        return m_self;
    }

private:

    static Network *m_self;
    int m_connfd;

    int mySocket(int family, int type, int protocol);
    void myConnect(int connfd, struct sockaddr *servaddr, int servaddrlen);
};

#endif // NETWORK_H
