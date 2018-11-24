//commenting complete
#include "initialization.c"
#include "fire.c"
#include "tankMovements.c"

#ifndef DEFENSE
#define DEFENSE

//spins the around in a circle, firing off all of the remaining ammo.
//This is run when the goose has been attacked.
//This function was tested by 'attacking' the tank and verifying proper behaviour
void defend (Tank tank0, Stats mission)
{
	float turn = 2 * 3.14159 / mission.ammoRemaining;
	bool isAttackedExtra = true; //this function is only run if the robot has been attacked, but we still need a bool to pass to the firing function
	for (int shots = 0; shots < mission.ammoRemaining; shots ++)
	{
		turnAngle(tank0, turn + tank0.angle, isAttackedExtra);
		fire(isAttackedExtra);
	}
}

#endif
