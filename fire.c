#include "initialization.c"
#include "attacked.c"

#ifndef FIRE
#define FIRE

//FIRING

//loads the next ball into the shooting position
void reload(bool & isAttacked)
{
	nMotorEncoder(hopperMotor) = 0;
	motor[hopperMotor] = 10;
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
	while(nMotorEncoder[firingMotor] < 718) //720 because geared up
	{				//-10 for offset
		isAttacked = attacked(isAttacked);
	}
	motor[firingMotor] = 0;
	reload(isAttacked);
}

#endif
