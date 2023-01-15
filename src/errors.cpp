#include "../include/serial_lib/errors.hpp"

namespace serial_lib
{
    namespace errors
    {
        Error::Error()
        {
            codeDetails = {
            {ErrorCode::NO_ERROR, "No errors."},
            {ErrorCode::DEVICE_NAME_EMPTY, "Empty device name."},
            {ErrorCode::CANT_OPEN_DEVICE, "Can't open device."},
            {ErrorCode::UNKNOWN_BAUD_RATE, "Incorrect Baud Rate."},
            {ErrorCode::INVALID_NUMBER_OF_DATA_BITS, "Invalid number of data bits."},
            {ErrorCode::INVALID_PARITY, "Invalid parity."},
            {ErrorCode::INVALID_STOP_BITS, "Invalid number of stop bits."},
            {ErrorCode::INVALID_HARDWARE_CONTROL_FLOW_SPECIFICATION, "Invalid specification of hardware control flow."},
            {ErrorCode::PORT_CLOSE_FAILED, "Can't close port."},
            {ErrorCode::FILE_NOT_OPEN, "File description not opened."},
            {ErrorCode::PORT_NOT_OPEN, "Port not open."}
                };    
        }

        std::string Error::give(ErrorCode err)
        {
            auto found = codeDetails.find(err);

            if(found != codeDetails.end())
                return found->second;

            return "aaaaaaaaa";
        }
    }

    
}