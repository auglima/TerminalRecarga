#include "gaveta.h"

Gaveta::Gaveta(
        BlackLib::gpioName ledR, BlackLib::gpioName ledG,
        BlackLib::gpioName ledB, BlackLib::gpioName chave,
        BlackLib::gpioName ambiente, std::string sensor) :
    m_ledR(new BlackLib::BlackGPIO(ledR, BlackLib::output, BlackLib::SecureMode)),
    m_ledG(new BlackLib::BlackGPIO(ledG, BlackLib::output, BlackLib::SecureMode)),
    m_ledB(new BlackLib::BlackGPIO(ledB, BlackLib::output, BlackLib::SecureMode)),
    m_chave(new BlackLib::BlackGPIO(chave, BlackLib::input, BlackLib::SecureMode)),
    m_ambiente(new BlackLib::BlackGPIO(ambiente, BlackLib::output, BlackLib::SecureMode)),
    m_sensor(sensor),
    m_estado(DISPONIVEL),
    m_plugado(false),
    m_alive(true)
{
    m_ledR->setValue(BlackLib::low);
    m_ledG->setValue(BlackLib::low);
    m_ledB->setValue(BlackLib::low);

    std::cout << "Iniciando gaveta\n";
}

Gaveta::~Gaveta()
{
    delete m_ledR;
    delete m_ledG;
    delete m_ledB;
    delete m_chave;
    delete m_ambiente;

    m_alive = false;

    if (m_thread.joinable()) m_thread.join();

    std::cout << "Destruindo gaveta\n";
}

void Gaveta::iniciar()
{
    m_thread = std::thread(&Gaveta::executar, this);
}

void Gaveta::executar()
{
    std::cout << "Executando thread " << std::this_thread::get_id() << std::endl;

    while(m_alive)
    {
         m_plugado = (sensor() > 10) ? true : false; //mudar escala

        if (!m_chave->isHigh() && !m_plugado)
        {
            m_estado = DISPONIVEL;
            m_ledR->setValue(BlackLib::low);
            m_ledG->setValue(BlackLib::high);
            m_ledB->setValue(BlackLib::low);
        }
        else if(m_chave->isHigh() && m_plugado)
        {
            m_estado = OCUPADO;
            m_ledR->setValue(BlackLib::low);
            m_ledG->setValue(BlackLib::low);
            m_ledB->setValue(BlackLib::low);
        }
        else if(!m_chave->isHigh() && m_plugado)
        {
            m_estado = PERIGO;
            m_ledR->setValue(BlackLib::high);
            m_ledG->setValue(BlackLib::low);
            m_ledB->setValue(BlackLib::low);
        }
        else
        {
            m_estado = SABOTADO;
            m_ledR->setValue(BlackLib::high);
            m_ledG->setValue(BlackLib::high);
            m_ledB->setValue(BlackLib::low);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int Gaveta::sensor()
{
    int number;

    std::stringstream stream;
    stream << m_sensor << number << "_raw";

    std::fstream file;
    file.open(stream.str().c_str(), std::fstream::in);
    file >> number;
    file.close();

    return 20;
}

int Gaveta::status()
{
    return (int)m_estado;
}
