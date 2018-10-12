#ifndef __CONNECTION_REFUSED_EXCEPTION_H__
#define __CONNECTION_REFUSED_EXCEPTION_H__

#include <stdexcept>

class ConnectionRefusedException : public std::runtime_error {
public:
	ConnectionRefusedException();
};


#endif //__CONNECTION_REFUSED_EXCEPTION_H__
