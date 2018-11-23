#include "initialization.c"
#ifndef ATTACKED
#define ATTACKED

bool attacked(bool const & isAttacked)
{
	//if (SensorValue(touch1) == 1 || SensorValue(touch2) == 1)
	if (SensorValue(touch1) == 1){
		return true;
	}
	return isAttacked;
}

#endif
