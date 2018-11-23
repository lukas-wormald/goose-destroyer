#include "initialization.c"
#include "fire.c"

#ifndef GOOSE_CHECK
#define GOOSE_CHECK

bool checkForGoose(bool & isAttacked)
{
	time1[T2] = 0;
	while(time1[T2] < 1000)
	{
		wait1Msec (1);
		isAttacked = attacked(isAttacked);
	}
	displayString(5, "%d", SensorValue(ultraSonic));
	return (RANGE - GOOSETOL < SensorValue(ultraSonic) && RANGE + GOOSETOL > SensorValue(ultraSonic));
}

//firing procedure
void shootTheGoose(int & ammoRemaining, Tank & tank1, bool & isAttacked)
{
	//Always shoots one ball at target area
	bool gooseIsThere = true;
	while (gooseIsThere && !isAttacked)
	{
		fire(isAttacked);
		ammoRemaining --;
		gooseIsThere = checkForGoose(isAttacked);
		if (gooseIsThere)
		{
		}
	}
}

#endif
