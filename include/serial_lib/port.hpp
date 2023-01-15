#ifndef PORT_HPP
#define PORT_HPP

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
//#include <asm/termios.h>
#include <errno.h>
#include <asm/termbits.h>
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
         * @brief Use the setter functions to specify custom values.
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
            utils::Parity parity,
            utils::DataBits num_data_bits,
            utils::StopBits num_stop_bits,
            int32_t timeout_ms,
            bool echo = false
        );

        Port(
            const std::string& port_name,
            utils::PortMode port_mode,
            utils::BaudRate baud_rate,
            utils::Parity parity,
            utils::DataBits num_data_bits,
            utils::StopBits num_stop_bits,
            int32_t timeout_ms,
            utils::HFC use_hardware_flow_control,
            utils::SFC use_software_flow_control,
            bool echo = false
        );

        ~Port();

        errors::ErrorCode openPort();

        errors::ErrorCode closePort();

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

        inline utils::PortState getState() const
        {
            return m_PortState;
        }

        errors::ErrorCode WriteString(const std::string& string_to_write);

        private:

        std::string m_PortName;

        utils::Utils m_Utils;

        utils::PortMode m_PortMode = utils::PortMode::READ_AND_WRITE;

        utils::BaudRate m_BaudRate = utils::BaudRate::BR_9600;

        utils::Parity m_Parity = utils::Parity::ODD;

        utils::DataBits m_DataBits = utils::DataBits::SEVEN;

        utils::StopBits m_StopBits = utils::StopBits::ONE;

        utils::PortState m_PortState = utils::PortState::CLOSED;

        utils::HFC m_HardwareFlowControl = utils::HFC::OFF;

        utils::SFC m_SoftwareFlowControl = utils::SFC::ON;

        // Timeout in [ms]
        int32_t m_Timeout; 
        
        int32_t m_DefaultTimeout = -1;

        bool m_EnableEcho;

        int m_FileDescription;

        errors::ErrorCode configure();


        

    };  
}

#endif