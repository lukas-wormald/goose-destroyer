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
		isAttacked = attacked();
	}
	motor[hopperMotor] = 0;
}

//FIRE
void fire(bool & isAttacked)
{
	nMotorEncoder[firingMotor] = 0;
	motor[firingMotor] = FIRESPEED;
	while(nMotorEncoder[firingMotor] < 718) //720 because NXT motor only rotated halfway with 360
	{				//-10 for offset
		isAttacked = attacked();
	}
	motor[firingMotor] = 0;
	reload(isAttacked);
}


//testing MAIN

task main()
{
	while(true)
	{
		bool garbage = false;
		fire(garbage);
		wait1Msec(2000);
	}
}


#endif
