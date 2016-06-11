#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

#include "socket.h"
#include "packet.h"


int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        std::cout << "Erro, Use: " << argv[0] << " hostname port";
        std::exit(EXIT_FAILURE);
    }

    std::cout << "*-----------------------------------------*" << '\n';
    std::cout << "| Servidor: terminais de recarga          |" << '\n';
    std::cout << "| Versão: alpha                           |" << '\n';
    std::cout << "*-----------------------------------------*" << '\n';

    Socket servidor(argv[1], atoi(argv[2]));

    servidor.conectar();

    return EXIT_SUCCESS;
}
