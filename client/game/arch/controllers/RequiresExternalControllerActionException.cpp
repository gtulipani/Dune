#include "RequiresExternalControllerActionException.h"

RequiresExternalControllerActionException::RequiresExternalControllerActionException() :
    runtime_error("Requires an action from an external controller") {}
