#ifndef UTILS_HPP
#define UTILS_HPP

namespace serial_lib
{
    namespace utils
    {

        enum class PortMode
        {
            READ_ONLY,
            WRITE_ONLY,
            READ_AND_WRITE
        };

        enum class BaudRate
        {
            BR_0,
            BR_50,
            BR_75,
            BR_110,
            BR_134,
            BR_150,
            BR_200,
            BR_300,
            BR_600,
            BR_1200,
            BR_1800,
            BR_2400,
            BR_4800,
            BR_9600,
            BR_19200,
            BR_38400,
            BR_57600,
            BR_115200,
            BR_230400,
            BR_460800
        };

        enum class Parity
        {
            NONE,
            EVEN,
            ODD
        };

        enum class StopBits
        {
            ONE,
            TWO
        };

        enum class DataBits
        {
            FIVE,
            SIX,
            SEVEN,
            EIGHT
        };

        enum PortState
        {
            OPENED,
            CLOSED
        };
    }
}

#endif