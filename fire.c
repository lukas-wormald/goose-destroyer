// commenting complete
#include "initialization.c"
#include "attacked.c"

#ifndef FIRE
#define FIRE

//FIRING

//loads the next ball into the shooting position
void reload(bool & isAttacked)
{
	nMotorEncoder(hopperMotor) = 0;
	motor[hopperMotor] = HOPPERSPEED;
	while(nMotorEncoder(hopperMotor) < 360/NUMBALLS-1)// && !isAttacked)
	{
		isAttacked = attacked(isAttacked);
	}
	motor[hopperMotor] = 0;
}

//FIRE
void fire(bool & isAttacked)
{
	nMotorEncoder[firingMotor] = 0;
	motor[firingMotor] = FIRESPEED;
	while(nMotorEncoder[firingMotor] < 718) //720 since geared up
	{					//-2 for offset from the rotation
		isAttacked = attacked(isAttacked);
	}
	motor[firingMotor] = 0;
	reload(isAttacked);
}

#endif

/*
//Testing main
task main()
{
	bool garbage = false;
	while(true)
	{
		TEV3Buttons test = getButtonPressed();
		fire(garbage);
	}
}
*/
