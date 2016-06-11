#include <iostream>
#include <unistd.h>
#include <string>

#include "socket.h"
#include "gaveta.h"
#include "BlackLib/v3_0/BlackGPIO/BlackGPIO.h"

#define PATH_ADC0 "/sys/bus/iio/devices/iio:device0/in_voltage"
#define PATH_ADC1 "/sys/bus/iio/devices/iio:device1/in_voltage"
#define PATH_ADC2 "/sys/bus/iio/devices/iio:device2/in_voltage"
#define PATH_ADC3 "/sys/bus/iio/devices/iio:device3/in_voltage"


int main(int argc, char *argv[])
{
    if(argc < 4)
    {
        std::cout << "Erro, Use: " << argv[0] << " hostname port terminal";
        std::exit(EXIT_FAILURE);
    }

    Socket socket(argv[1], atoi(argv[2]));


    Gaveta gaveta1(
                BlackLib::GPIO_2, BlackLib::GPIO_3, BlackLib::GPIO_4,
                BlackLib::GPIO_5, BlackLib::GPIO_7, PATH_ADC0);

    Gaveta gaveta2(
                BlackLib::GPIO_8, BlackLib::GPIO_9, BlackLib::GPIO_10,
                BlackLib::GPIO_11, BlackLib::GPIO_14, PATH_ADC1);

    Gaveta gaveta3(
                BlackLib::GPIO_15, BlackLib::GPIO_20, BlackLib::GPIO_22,
                BlackLib::GPIO_23, BlackLib::GPIO_26, PATH_ADC2);

    Gaveta gaveta4(
                BlackLib::GPIO_27, BlackLib::GPIO_30, BlackLib::GPIO_31,
                BlackLib::GPIO_32, BlackLib::GPIO_33, PATH_ADC3);

    gaveta1.iniciar();
    gaveta2.iniciar();
    gaveta3.iniciar();
    gaveta4.iniciar();

    usleep(2000);

    Packet oldPacket;
    Packet packet;


    while(1)
    {

        packet = Packet(atoi(argv[3]), gaveta1.status(), gaveta2.status(), gaveta3.status(), gaveta4.status());

        if (!(packet == oldPacket))
        {
            socket.enviar(packet);

            oldPacket = packet;
        }

        usleep(1000);
    };

    return EXIT_SUCCESS;
}
