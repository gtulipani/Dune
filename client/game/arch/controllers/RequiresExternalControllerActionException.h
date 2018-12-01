#ifndef __REQUIRES_EXTERNAL_CONTROLLER_ACTION_EXCEPTION_H__
#define __REQUIRES_EXTERNAL_CONTROLLER_ACTION_EXCEPTION_H__

#include <stdexcept>

class RequiresExternalControllerActionException : public std::runtime_error {
public:
    RequiresExternalControllerActionException();
};


#endif //__REQUIRES_EXTERNAL_CONTROLLER_ACTION_EXCEPTION_H__
