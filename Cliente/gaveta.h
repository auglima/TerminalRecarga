#ifndef GAVETA_H
#define GAVETA_H

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
#include "BlackLib/v3_0/BlackGPIO/BlackGPIO.h"

/**
 * @brief The Gaveta class
 * @version alpha
 */
class Gaveta
{
public:
    enum estado { DISPONIVEL=0, OCUPADO=1, PERIGO=2, SABOTADO=3 };

    Gaveta( BlackLib::gpioName ledR,
            BlackLib::gpioName ledG,
            BlackLib::gpioName ledB,
            BlackLib::gpioName chave,
            BlackLib::gpioName ambiente,
            std::string sensor);

    ~Gaveta();

    void iniciar();
    void executar();
    int  sensor();
    int  status();

private:
    BlackLib::BlackGPIO *m_ledR;
    BlackLib::BlackGPIO *m_ledG;
    BlackLib::BlackGPIO *m_ledB;
    BlackLib::BlackGPIO *m_chave;
    BlackLib::BlackGPIO *m_ambiente;

    std::string          m_sensor;
    estado               m_estado;
    bool                 m_plugado;

    bool                 m_alive;
    std::thread          m_thread;
};

#endif // GAVETA_H
