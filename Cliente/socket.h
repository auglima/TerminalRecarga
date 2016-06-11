#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "packet.h"

class Socket
{
public:
    Socket(char* host, int port);
    ~Socket();

    void enviar(Packet packet);

private:
    char* m_host;
    int   m_port;

    int   m_socket;

    struct sockaddr_in m_server;
};

#endif // SOCKET_H
