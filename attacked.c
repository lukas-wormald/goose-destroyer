#include "initialization.c"
#ifndef ATTACKED
#define ATTACKED

bool attacked()
{
	if (SensorValue(touch1) == 1 || SensorValue(touch2) == 1)
		return true;
	return false;
}

#endif
