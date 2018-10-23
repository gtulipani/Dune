#include "SOException.h"

#include <string.h> // For strerror

SOException::SOException() : runtime_error(strerror(errno)) {}

SOException::SOException(std::string _errmsg) : runtime_error(_errmsg) {}
