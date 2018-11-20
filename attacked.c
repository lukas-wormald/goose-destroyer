#include "initialization.c"
#ifndef ATTACKED
#define ATTACKED

bool attacked()
{
	if (SensorValue(touch) == 1)
		return true;
	return false;
}

#endif
