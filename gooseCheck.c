#include "initialization.c"
#include "fire.c"

#ifndef GOOSE_CHECK
#define GOOSE_CHECK

bool checkForGoose(bool & isAttacked)
{
	for (int count = 0; count < 1000 && !isAttacked; count ++)
	{
		wait1Msec (1);
		isAttacked = attacked();
	}
	return (RANGE - GOOSETOL < SensorValue(ultraSonic) && RANGE + GOOSETOL > SensorValue(ultraSonic));
}

//firing procedure
void shootTheGoose(int & ammoRemaining, Tank & tank1, bool & isAttacked)
{
	//Always shoots one ball at target area
	bool gooseIsThere = true;
	while (gooseIsThere)
	{
		fire(isAttacked);
		ammoRemaining --;
		gooseIsThere = checkForGoose(isAttacked);
	}
}

#endif
