#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <cstring>
#include <sstream>

/**
 * @brief The Packet class
 * @version alpha
 */
class Packet
{
public:
    Packet() : _terminal(0), _gaveta1(0), _gaveta2(0), _gaveta3(0), _gaveta4(0)
    { }

    Packet(int terminal, int gaveta1, int gaveta2, int gaveta3, int gaveta4) :
        _terminal(terminal),
        _gaveta1(gaveta1),
        _gaveta2(gaveta2),
        _gaveta3(gaveta3),
        _gaveta4(gaveta4)
    { }

    Packet(std::string s)
    {
        unserialize(s);
    }

    Packet& operator= (const Packet& rhs)
    {
        _terminal = rhs._terminal;
        _gaveta1  = rhs._gaveta1;
        _gaveta2  = rhs._gaveta2;
        _gaveta3  = rhs._gaveta3;
        _gaveta4  = rhs._gaveta4;
        return *this;
    }

    bool operator== (const Packet& rhs) const
    {
        if (_terminal == rhs._terminal)
            if (_gaveta1 == rhs._gaveta1)
                if (_gaveta2 == rhs._gaveta2)
                    if (_gaveta3 == rhs._gaveta3)
                        if (_gaveta4 == rhs._gaveta4)
                            return true;
        return false;
    }

    std::string serialize()
    {
        std::string msg = "";
        msg  = std::to_string(_terminal) + " " + std::to_string(_gaveta1) + " ";
        msg += std::to_string(_gaveta2) + " " + std::to_string(_gaveta3) + " ";
        msg += std::to_string(_gaveta4);
        return msg;
    }

    void unserialize(const std::string &s)
    {
        std::stringstream ss(s);
        ss >> _terminal;
        ss >> _gaveta1;
        ss >> _gaveta2;
        ss >> _gaveta3;
        ss >> _gaveta4;
    }

private:
    int _terminal;
    int _gaveta1;
    int _gaveta2;
    int _gaveta3;
    int _gaveta4;
};

#endif // PACKET_H
