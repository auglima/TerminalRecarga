#include "socket.h"

Socket::Socket(char *host, int port) :
    m_host(host), m_port(port)
{
    memset(&m_server, 0, sizeof(m_server));
    m_server.sin_family = AF_INET;
    m_server.sin_port   = htons(m_port);
    m_server.sin_addr.s_addr = inet_addr(m_host);

    m_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_socket == -1)
    {
        std::perror("Falha ao executar socket()");
        std::exit(EXIT_FAILURE);
    }
    std::cout << "Socket criado!\n";

    if (connect(m_socket, (struct sockaddr *)&m_server, sizeof(sockaddr)) == -1)
    {
        std::perror("Falha ao executar connect()");
        std::exit(EXIT_FAILURE);
    }
    std::cout << "Cliente conectado ao servidor!\n";
}

Socket::~Socket()
{
    ::close(m_socket);
}

void Socket::enviar(Packet packet)
{
    std::string msg = packet.serialize();

    char m[32];
    std::copy(msg.begin(), msg.end(), m);
    m[msg.size()] = '\0';

    int bytes = send(m_socket, &m, sizeof(m), 0);

    if (bytes == -1)
        std::perror("Falha ao executar connect()");
    else
        std::cout << "Enviado " << msg << '\n';
}
