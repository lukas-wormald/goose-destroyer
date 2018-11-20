#include "initialization.c"
#include "fire.c"

#ifndef GOOSE_CHECK
#define GOOSE_CHECK

bool checkForGoose()
{
	wait1Msec (1000);
	return (RANGE - GOOSETOL < SensorValue(ultraSonic) && RANGE + GOOSETOL > SensorValue(ultraSonic));
}

//firing procedure
void shootTheGoose(int & ammoRemaining, Tank & tank1)
{
	//Always shoots one ball at target area
	bool gooseIsThere = true;
	while (gooseIsThere)
	{
		fire();
		ammoRemaining --;
		gooseIsThere = checkForGoose();
	}
}

#endif
