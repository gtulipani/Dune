#include "SOException.h"

#include <cstring>
#include <cerrno> // For errno

SOException::SOException() : runtime_error(std::strerror(errno)) {}

SOException::SOException(std::string message) : runtime_error(message) {}
