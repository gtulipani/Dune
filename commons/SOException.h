#ifndef __SO_EXCEPTION_H__
#define __SO_EXCEPTION_H__

#include <stdexcept>

class SOException : public std::runtime_error {
    public:
    SOException();

    SOException(std::string _errmsg);
};

#endif // __SO_EXCEPTION_H__
