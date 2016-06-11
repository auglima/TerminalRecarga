#include "socket.h"

Socket::Socket(const char* _host, const int _porta) :
    m_host(_host),
    m_porta(_porta)
{
    std::cout << "Inicializando servidor\n";
    std::cout << "Hostname: " << m_host << " Porta: " << m_porta << "\n\n";
}

Socket::~Socket()
{
    ::close(m_socket);
}

void Socket::conectar()
{
    memset(&m_addr_servidor, 0, sizeof(m_addr_servidor));
    m_addr_servidor.sin_family      = AF_INET;
    m_addr_servidor.sin_port        = htons(m_porta);
    m_addr_servidor.sin_addr.s_addr = inet_addr(m_host);

    m_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_socket == -1)
    {
        std::cout << "Falha ao executar socket()!\n";
        std::exit(EXIT_FAILURE);
    }

    if (bind(m_socket, (struct sockaddr *)&m_addr_servidor, sizeof(struct sockaddr)) == -1)
    {
        std::cout << "Falha ao executar bind()!\n";
        std::exit(EXIT_FAILURE);
    }

    if (listen(m_socket, 10) == -1)
    {
        std::cout << "Falha ao executar listen()!\n";
        std::exit(EXIT_FAILURE);
    }

    std::cout << "Esperando conexões clientes:\n";

    while(1)
    {
        m_socket_cliente = accept(m_socket, (struct sockaddr *)&m_addr_cliente, &m_client_size);

        std::cout << "recebeu conexão de " << inet_ntoa(m_addr_cliente.sin_addr) << "\n";

        std::thread t(&Socket::cliente, this, m_socket_cliente);
        t.detach();
    }

}

void Socket::cliente(int socket)
{

    char msg[32];

    if (socket == -1)
    {
        std::cout << "Falha ao executar accept()!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    while (1)
    {
        int byteslidos = recv(socket, &msg, sizeof(msg), 0);

        if (byteslidos == 0)
        {
            std::cout << "Cliente finalizou a conexão()!" << std::endl;
            break;
            //std::exit(EXIT_FAILURE);
        }
        else if (byteslidos == -1)
        {
            std::cout << "Falha ao executar recv()!" << std::endl;
            continue;
        }
        else
        {
            std::cout << "Servidor recebeu msg: " << msg << std::time(0) << std::endl;
        }
    }

    ::close(socket);
}
