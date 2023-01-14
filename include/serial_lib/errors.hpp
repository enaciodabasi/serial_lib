#ifndef ERRORS_HPP
#define ERRORS_HPP

namespace serial_lib
{
    namespace errors
    {
        enum class ErrorCode
        {   
            NO_ERROR,
            DEVICE_NAME_EMPTY,
            CANT_OPEN_DEVICE
        };
    }
}

#endif