#include "initialization.c"
#include "attacked.c"

#ifndef FIRE
#define FIRE

//FIRING

//loads the next ball into the shooting position
void reload()
{
	nMotorEncoder(hopperMotor) = 0;
	motor[hopperMotor] = 20;
	//bool isAttacked = false;
	while(nMotorEncoder(hopperMotor) < 360/NUMBALLS)// && !isAttacked)
	{
		//isAttacked = attacked();
	}
	motor[hopperMotor] = 0;
}

//FIRE
void fire()
{
	nMotorEncoder[firingMotor] = 0;
	motor[firingMotor] = FIRESPEED;
	while(nMotorEncoder[firingMotor] > -360)
	{}
	motor[firingMotor] = 0;
	reload();
}

#endif
