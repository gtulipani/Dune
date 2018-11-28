#ifndef __REQUIRES_EXTRA_ACTION_EXCEPTION_H__
#define __REQUIRES_EXTRA_ACTION_EXCEPTION_H__

#include <stdexcept>

class RequiresTerrainControllerActionException : public std::runtime_error {
public:
    RequiresTerrainControllerActionException();
};


#endif //__REQUIRES_EXTRA_ACTION_EXCEPTION_H__
