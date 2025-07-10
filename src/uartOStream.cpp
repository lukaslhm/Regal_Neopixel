#include "uartOStream.hpp"

#include <Arduino.h>
#include <stdio.h>
#include <iostream>

#include <sstream>

class uart0StreamBuf : public std::streambuf
{
public:
    uart0StreamBuf() {Serial.begin(9600);}

    int_type overflow(int_type c) override
    {
        if (c == '\n')
        {
            Serial.println(lineBuffer.str().c_str());
            lineBuffer.clear();
            lineBuffer.str("");
        }
        else
        {
            lineBuffer << (char) c;
        }

        return c;
    }

    int_type sync() override
    {
        Serial.print("Activated");
        Serial.print(lineBuffer.str().c_str());
        lineBuffer.clear();
        lineBuffer.str("");
    }

private:
    std::stringstream lineBuffer;
};

uart0StreamBuf buf;
std::ostream UART0::uartOut(&buf);
