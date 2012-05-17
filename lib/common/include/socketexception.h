#ifndef __SOCKETEXCEPTION_H__
#define __SOCKETEXCEPTION_H__

#include <string>
#include <exception>

class SocketException : public exception
{
    public:
        SocketException(const std::string & message, bool inclSysMsg = false) throw();

        ~SocketException() throw();

        const char* what() const throw();

    private:
        std::string message;
};

#endif //__SOCKETEXCEPTION_H__
