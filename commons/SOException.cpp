#include "SOException.h"

#include <string.h> // For strerror

SOException::SOException() {
    errmsg = strerror(errno);
}

SOException::SOException(std::string _errmsg) : errmsg(_errmsg) {}

const char*
SOException::what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT {
    return errmsg.c_str();
}
