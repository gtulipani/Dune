#ifndef __SO_EXCEPTION_H__
#define __SO_EXCEPTION_H__

#include <stdexcept>

class SOException : public std::exception {
    private:
    std::string errmsg;

    public:
    SOException();

    SOException(std::string _errmsg);

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT;
};

#endif
