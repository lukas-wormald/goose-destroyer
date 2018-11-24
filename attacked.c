#include "initialization.c"
#ifndef ATTACKED
#define ATTACKED

bool attacked(bool const & isAttacked)
{
	//checks if the goose is still there
	if (SensorValue(touch1) == 1)
	{
		return true;
	}
	//if it was already attacked, it will return true again
	return isAttacked;
}

#endif
