#ifndef __BAD_FILE_EXCEPTION_H__
#define __BAD_FILE_EXCEPTION_H__

#include <stdexcept>

class BadFileException : public std::runtime_error {
public:
	BadFileException();
};


#endif //__BAD_FILE_EXCEPTION_H__
