#ifndef UTILS_HPP
#define UTILS_HPP

#include <map>

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
        /**
         * @brief Hardware Flow Control
         * 
         */
        enum class HFC
        {
            ON,
            OFF
        };

        /**
         * @brief Software Flow Control
         * 
         */
        enum class SFC
        {
            ON,
            OFF
        };

        enum class PortState
        {
            OPENED,
            CLOSED
        };

        class Utils
        {
            public:

            Utils();

            int getBaudRateAsInt(const BaudRate& baud_rate);

            int getDataBitsAsInt(const DataBits& num_data_bits);

            private:

            std::map<BaudRate, int> m_BaudRateMap;

            std::map<DataBits, int> m_DataBitsMap;

            void initBaudRateMap();

            void initDataBitsMap();

        };

    }
}

#endif