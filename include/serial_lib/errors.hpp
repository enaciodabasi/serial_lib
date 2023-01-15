#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <unordered_map>

namespace serial_lib
{
    namespace errors
    {
        enum class ErrorCode
        {   
            NO_ERROR,
            DEVICE_NAME_EMPTY,
            CANT_OPEN_DEVICE,
            UNKNOWN_BAUD_RATE,
            INVALID_NUMBER_OF_DATA_BITS,
            INVALID_PARITY,
            INVALID_STOP_BITS,
            INVALID_HARDWARE_CONTROL_FLOW_SPECIFICATION,
            PORT_CLOSE_FAILED,
            FILE_NOT_OPEN,
            PORT_NOT_OPEN
        };


        class Error
        {
            public:

            Error();

            std::string give(ErrorCode err);

            private:

            std::unordered_map<ErrorCode, std::string> codeDetails; 
        };
           
    }
}

#endif