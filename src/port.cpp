#include "port.hpp"

namespace serial_lib
{
    Port::Port()
    {
        
    }

    Port::Port(
        const std::string& port_name
    )   : m_PortName(port_name)
    {

    }

    Port::Port(
        const std::string& port_name,
        utils::PortMode port_mode,
        utils::BaudRate baud_rate,
        utils::Parity parity,
        utils::DataBits num_data_bits,
        utils::StopBits num_stop_bits
    )   :
        m_PortName(port_name),
        m_PortMode(port_mode),
        m_BaudRate(baud_rate),
        m_DataBits(num_data_bits),
        m_StopBits(num_stop_bits)
    {

    }

    errors::ErrorCode Port::openPort()
    {
        if(m_PortName.empty())
        {
            return errors::ErrorCode::DEVICE_NAME_EMPTY;
        }

        int oflag;

        switch (m_PortMode)
        {
        case utils::PortMode::READ_ONLY :
            oflag = O_RDONLY;
            break;
        case utils::PortMode::WRITE_ONLY :
            oflag = O_WRONLY;
            break;
        case utils::PortMode::READ_AND_WRITE :
            oflag = O_RDWR;
            break;
        default:
            oflag = O_RDWR;
            break;
        }

        m_FileDescription = open(
            m_PortName.c_str(),
            oflag
        );

        if(m_FileDescription < 0)
        {
            return errors::ErrorCode::CANT_OPEN_DEVICE;
        }

        

        m_PortState = utils::PortState::OPENED;

    }

    void Port::closePort()
    {

    }
}