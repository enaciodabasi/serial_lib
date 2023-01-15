#include "port.hpp"

namespace serial_lib
{
    Port::Port()
    {
        m_Utils = utils::Utils();
    }

    Port::Port(
        const std::string& port_name
    )   : m_PortName(port_name)
    {
        m_Utils = utils::Utils();
    }

    Port::Port(
        const std::string& port_name,
        utils::PortMode port_mode,
        utils::BaudRate baud_rate,
        utils::Parity parity,
        utils::DataBits num_data_bits,
        utils::StopBits num_stop_bits,
        int32_t timeout_ms,
        bool echo
    )   :
        m_PortName(port_name),
        m_PortMode(port_mode),
        m_BaudRate(baud_rate),
        m_Parity(parity),
        m_DataBits(num_data_bits),
        m_StopBits(num_stop_bits),
        m_Timeout(timeout_ms),
        m_EnableEcho(echo)
    {
        m_Utils = utils::Utils();
    }

    Port::Port(
        const std::string& port_name,
        utils::PortMode port_mode,
        utils::BaudRate baud_rate,
        utils::Parity parity,
        utils::DataBits num_data_bits,
        utils::StopBits num_stop_bits,
        int32_t timeout_ms,
        utils::HFC use_hardware_flow_control,
        utils::SFC use_software_flow_control,
        bool echo
        )   :
            m_PortName(port_name),
            m_PortMode(port_mode),
            m_BaudRate(baud_rate),
            m_Parity(parity),
            m_DataBits(num_data_bits),
            m_StopBits(num_stop_bits),
            m_Timeout(timeout_ms),
            m_HardwareFlowControl(use_hardware_flow_control),
            m_SoftwareFlowControl(use_software_flow_control),
            m_EnableEcho(echo)
        {
            m_Utils = utils::Utils();
        }

    Port::~Port()
    {
        closePort();
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
            O_RDWR
        );

        if(m_FileDescription == -1)
        {
            return errors::ErrorCode::CANT_OPEN_DEVICE;
        }



        m_PortState = utils::PortState::OPENED;

        

        return configure();

    }

    errors::ErrorCode Port::closePort()
    {
        if(m_FileDescription != -1)
        {
            int ret = close(m_FileDescription);

            if(ret != 0)
                return errors::ErrorCode::PORT_CLOSE_FAILED;

            m_FileDescription = -1;
        }

        m_PortState = utils::PortState::CLOSED;

        return errors::ErrorCode::NO_ERROR;
    }

    errors::ErrorCode Port::configure()
    {
        termios2 tty;
        ioctl(m_FileDescription, TCGETS2, &tty);

        // Setting the number of data bits

        tty.c_cflag &= ~CSIZE;

        int databits = m_Utils.getDataBitsAsInt(m_DataBits);
        
        if(databits == -1)
        {
            return errors::ErrorCode::INVALID_NUMBER_OF_DATA_BITS;
        }

        tty.c_cflag |= databits;

        // Setting the parity

        switch (m_Parity)
        {
        case utils::Parity::NONE:
            tty.c_cflag &= ~PARENB;
            break;
        case utils::Parity::EVEN:
            tty.c_cflag |= PARENB;
            tty.c_cflag &= ~PARODD;
        case utils::Parity::ODD:
            tty.c_cflag |= PARENB;
            tty.c_cflag |= PARODD;
        default:
            return errors::ErrorCode::INVALID_PARITY;   
        }

        // Setting the stop bits

        switch (m_StopBits)
        {
        case utils::StopBits::ONE:
            tty.c_cflag &= ~CSTOPB;
            break;
        case utils::StopBits::TWO:
            tty.c_cflag |= ~CSTOPB;
        default:
            return errors::ErrorCode::INVALID_STOP_BITS;
        }

        switch (m_HardwareFlowControl)
        {
        case utils::HFC::OFF:
            tty.c_cflag &= ~CRTSCTS;
            break;
        case utils::HFC::ON:
            tty.c_cflag |= CRTSCTS;
        default:
            return errors::ErrorCode::INVALID_HARDWARE_CONTROL_FLOW_SPECIFICATION;
        }

        // Setting the Baud Rate

        tty.c_cflag |= CREAD | CLOCAL;

        int baudrate = m_Utils.getBaudRateAsInt(m_BaudRate);

        if(baudrate == -1)
        {
            return errors::ErrorCode::UNKNOWN_BAUD_RATE;
        }

        tty.c_cflag &= ~CBAUD;
        tty.c_cflag |= CBAUDEX;

        tty.c_ispeed = baudrate;
        tty.c_ospeed = baudrate;

        tty.c_oflag = 0;
        tty.c_oflag &= ~OPOST;

        // Setting the timeout [ms]

        if(m_Timeout == -1)
        {
            tty.c_cc[VTIME] = 0;
            tty.c_cc[VMIN] = 1;
        }
        else if(m_Timeout == 0)
        {
            tty.c_cc[VTIME] = 0;
            tty.c_cc[VMIN] = 0;
        }
        else if(m_Timeout > 0 && m_Timeout < 25500)
        {
            tty.c_cc[VTIME] = (cc_t)(m_Timeout/100);    // 0.5 seconds read timeout
            tty.c_cc[VMIN] = 0;
        }
        else // Use default timeout
        {
            tty.c_cc[VTIME] = 0;
            tty.c_cc[VMIN] = 1;
        }

        // Setting the software flow control

        if(m_SoftwareFlowControl == utils::SFC::OFF)
        {
            tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        }
        else if(m_SoftwareFlowControl == utils::SFC::ON)
        {
            tty.c_iflag |= (IXON | IXOFF | IXANY);
        }

        tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

        tty.c_lflag &= ~ICANON;

        if(m_EnableEcho)
        {
            tty.c_lflag |= ECHO;
        }
        else
        {
            tty.c_lflag &= ~(ECHO);
        }

        tty.c_lflag &= ECHOE;

        tty.c_lflag &= ~ECHONL;
    
        tty.c_lflag &= ~ISIG;

        ioctl(
            m_FileDescription,
            TCSETS2,
            &tty
        );

        return errors::ErrorCode::NO_ERROR;
        
    }

    errors::ErrorCode Port::WriteString(const std::string& string_to_write)
    {
        if(m_PortState == utils::PortState::CLOSED)
        {
            return errors::ErrorCode::PORT_NOT_OPEN;
        }

        if(m_FileDescription < 0)
        {
            return errors::ErrorCode::FILE_NOT_OPEN;
        }

        int res = write(m_FileDescription, string_to_write.c_str(), string_to_write.size());

        if(res == -1)
        {
            std::cout << "error aq" << std::endl;
        }

        return errors::ErrorCode::NO_ERROR;
    }
}