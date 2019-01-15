#ifndef TCPNETWORK_H
#define TCPNETWORK_H

#include <sys/socket.h>
#include <stdlib.h>

#define SERV_PORT 6666

class TcpNetwork
{
public:
    TcpNetwork();

    //单例模式
    static TcpNetwork *single()
    {
        if (NULL == m_self)
        {
            m_self = new TcpNetwork();
        }

        return m_self;
    }

    void initNetwork();

    int getSockfd() const;

private:
    static TcpNetwork *m_self;

    int mySocket(int family, int type, int protocol);
    void myBind(int sockfd, const struct sockaddr *serverAddr,
                 socklen_t servAddrLen);
    void myListen(int sockfd, int backlog);

    int m_sockfd;

};

#endif // TCPNETWORK_H
