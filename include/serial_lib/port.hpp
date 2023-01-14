#ifndef PORT_HPP
#define PORT_HPP

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <asm/ioctls.h>
#include <asm/termios.h>
#include <errno.h>

#include "utils.hpp"
#include "errors.hpp"

namespace serial_lib
{
    class Port
    {
        public:

        /**
         * @brief Default constructor for creating a Port object.
         * setPortName function should be called after using the default constructor.
         */
        Port();

        /**
         * @brief Construct a new Port object without custom configurations.
         * @brief Please use the setter functions to specify custom values.
         * @param port_name Name of the serial port of the device. 
         */
        Port(
            const std::string& port_name
        );

        /**
         * @brief Construct a new Port object
         * 
         * @param port_name 
         * @param port_mode 
         * @param baud_rate 
         * @param parity 
         * @param num_data_bits 
         * @param num_stop_bits 
         */
        Port(
            const std::string& port_name,
            utils::PortMode port_mode,
            utils::BaudRate baud_rate,
            utils::Parity parity = utils::Parity::ODD,
            utils::DataBits num_data_bits = utils::DataBits::SEVEN,
            utils::StopBits num_stop_bits = utils::StopBits::ONE
        );

        ~Port();

        errors::ErrorCode openPort();

        void closePort();

        inline void setPortName(const std::string& port_name)
        {
            m_PortName = port_name;
        }

        inline void setPortMode(const utils::PortMode& port_mode)
        {
            m_PortMode = port_mode;
        }

        inline void setBaudRate(const utils::BaudRate& baud_rate)
        {
            m_BaudRate = baud_rate;
        }

        inline void setParity(const utils::Parity& parity)
        {
            m_Parity = parity;
        }
        
        inline void setDataBits(const utils::DataBits& num_data_bits)
        {
            m_DataBits = num_data_bits;
        }

        /**
         * @brief Set the number of stop bits of the port.
         * 
         * @param num_stop_bits Enum object of type StopBits
         */
        inline void setStopBits(const utils::StopBits& num_stop_bits)
        {
            m_StopBits = num_stop_bits;
        }


        private:

        std::string m_PortName;

        utils::PortMode m_PortMode = utils::PortMode::READ_AND_WRITE;

        utils::BaudRate m_BaudRate = utils::BaudRate::BR_9600;

        utils::Parity m_Parity = utils::Parity::ODD;

        utils::DataBits m_DataBits = utils::DataBits::SEVEN;

        utils::StopBits m_StopBits = utils::StopBits::ONE;

        utils::PortState m_PortState = utils::PortState::CLOSED;

        int m_FileDescription;

    };  
}

#endif