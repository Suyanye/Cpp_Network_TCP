#include <iostream>

#include "network.h"


int main()
{
    int connfd = 0;

    Network::single()->initNetwork();

    connfd = Network::single()->getConnfd();

    std::cout << connfd << std::endl;
    return 0;
}

