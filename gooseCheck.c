#include "initialization.c"
#include "fire.c"
#include "tankMovements.c"

#ifndef GOOSE_CHECK
#define GOOSE_CHECK

bool checkForGoose(bool & isAttacked)
{
	time1[T2] = 0;
	//wait one second to see if the goose flew away or not
	while(time1[T2] < 1000)
	{
		wait1Msec (1);
		isAttacked = attacked(isAttacked);
	}
	int distance = SensorValue(ultraSonic);
	//Returns if there is something within the tolerance of the original goose's location
	return (RANGE - GOOSETOL < distance && RANGE + GOOSETOL > distance);
}

//firing procedure
void shootTheGoose(Stats mission, Tank & tank0)
{
	//Always shoots one ball at target area
	bool gooseIsThere = true;
	while (gooseIsThere && !mission.isAttacked && mission.ammoRemaining > 0)
	{
		fire(mission.isAttacked);
		mission.ammoRemaining--;

		//turn back (firing is offset), then check for goose
		turnAngle(tank0, tank0.angle+degToRad(OFFSETANGLE), mission.isAttacked);

		gooseIsThere = checkForGoose(mission.isAttacked);
		if (gooseIsThere)//if the goose is still there, turn back so it can shoot it.
		{
			turnAngle(tank0, tank0.angle-degToRad(OFFSETANGLE), mission.isAttacked);
		}
	}
}

#endif
