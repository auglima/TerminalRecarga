#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include <ctime>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "packet.h"

/**
 * @brief The Socket class
 * @version alpha
 */
class Socket
{
public:
    Socket(const char* _host, const int _porta);
    ~Socket();

    void conectar();

    void cliente(int socket);

private:
    const char *m_host;
    const int   m_porta;

    int m_socket;
    struct sockaddr_in m_addr_servidor;

    int m_socket_cliente;
    struct sockaddr_in m_addr_cliente;
    socklen_t m_client_size = sizeof(struct sockaddr);
};

#endif // SOCKET_H
