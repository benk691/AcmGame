#include "socketexception.h"

#include <errno.h>

SocketException::SocketException(const std::string & message, bool inclSysMsg = false) throw()
    : message(message)
{
    if(inclSysMsg)
    {
        message.append(": ");
        message.append(strerror(errno));
    }
}

SocketException::~SocketException() throw()
{}

const char* SocketException::what() const throw()
{
    return message.c_str();
}
