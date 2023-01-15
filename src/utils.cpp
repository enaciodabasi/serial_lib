#include "utils.hpp"

#include <asm/termbits.h>

namespace serial_lib
{
    namespace utils
    {
        Utils::Utils()
        {
            initBaudRateMap();
            initDataBitsMap();
        }

        int Utils::getBaudRateAsInt(const BaudRate& baud_rate)
        {
            auto found = m_BaudRateMap.find(baud_rate);
            if(found != m_BaudRateMap.end())
            {
                return found->second;
            }

            return -1;
        }

        int Utils::getDataBitsAsInt(const DataBits& num_data_bits)
        {
            auto found = m_DataBitsMap.find(num_data_bits);
            if(found != m_DataBitsMap.end())
            {
                return found->second;
            }

            return -1;
        }

        void Utils::initBaudRateMap()
        {
            m_BaudRateMap[BaudRate::BR_0] = 0;
            m_BaudRateMap[BaudRate::BR_50] = 50;
            m_BaudRateMap[BaudRate::BR_75] = 75;
            m_BaudRateMap[BaudRate::BR_110] = 110;
            m_BaudRateMap[BaudRate::BR_134] = 134;
            m_BaudRateMap[BaudRate::BR_150] = 150;
            m_BaudRateMap[BaudRate::BR_200] = 200;
            m_BaudRateMap[BaudRate::BR_300] = 300;
            m_BaudRateMap[BaudRate::BR_600] = 600;
            m_BaudRateMap[BaudRate::BR_1200] = 1200;
            m_BaudRateMap[BaudRate::BR_1800] = 1800;
            m_BaudRateMap[BaudRate::BR_2400] = 2400;
            m_BaudRateMap[BaudRate::BR_4800] = 4800;
            m_BaudRateMap[BaudRate::BR_9600] = 9600;
            m_BaudRateMap[BaudRate::BR_19200] = 19200;
            m_BaudRateMap[BaudRate::BR_38400] = 38400;
            m_BaudRateMap[BaudRate::BR_57600] = 57600;
            m_BaudRateMap[BaudRate::BR_115200] = 115200;
            m_BaudRateMap[BaudRate::BR_230400] = 230400;
            m_BaudRateMap[BaudRate::BR_460800] = 460900;
        }

        void Utils::initDataBitsMap()
        {
            m_DataBitsMap[DataBits::FIVE] = CS5;
            m_DataBitsMap[DataBits::SIX] = CS6;
            m_DataBitsMap[DataBits::SEVEN] = CS7;
            m_DataBitsMap[DataBits::EIGHT] = CS8;
        }
    }
}