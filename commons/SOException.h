#ifndef __SO_EXCEPTION_H__
#define __SO_EXCEPTION_H__

#include <stdexcept>
#include <string>

class SOException : public std::runtime_error {
public:
    SOException();

    SOException(std::string message);
};

#endif // __SO_EXCEPTION_H__
