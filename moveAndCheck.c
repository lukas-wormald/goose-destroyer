#include "initialization.c"
#include "calculations.c"
#include "attacked.c"
#ifndef MOVE_AND_CHECK
#define MOVE_AND_CHECK

//IMPLEMENT ATTACKING IF WE HAVE TIME

//Tank Movements

//TANK OPERATIONS
//TANK MOTION
//driveForward set distance
float drive (float distance) //TESTED Can Drive set distances
{
	nMotorEncoder[leftMotor] = 0;
	motor[leftMotor] = motor[rightMotor] = -SPEED; //Needs to be negative to go forward
	bool isAttacked = false;
	while(-nMotorEncoder[leftMotor] / 360.0 * GEARRADIUS * 2 * PI < distance && !isAttacked)
	{
		isAttacked = attacked();
	}
	motor[leftMotor] = motor[rightMotor] = 0;
	//returns the distance traveled
	return -nMotorEncoder[leftMotor] / 360.0 * GEARRADIUS * 2 * PI;
}

void turnAngle (Tank & tank0, float rotation)  //TESTED  WORKS BEST WHEN SLOWER SPEED
{
	//1 counter clockwise
	int direction = 1;
	if (rotation-tank0.angle<0)
	{
		//turn clockwise
		direction = -1;
	}
	//default is counter clockwise
	motor[leftMotor] = - direction * SPEED / 3;
	motor[rightMotor] = direction * SPEED / 3;
	resetGyro(gyro);
	bool isAttacked = false;

	displayString(3, "Gyro: %d       ", getGyroRadians());
	displayString(2, "Direction: %d       ", rotation);
	while(direction*rotation > direction * (-getGyroRadians()+ tank0.angle) && !isAttacked)
	{
		isAttacked = attacked();
	}
	displayString(3, "Gyro: %d       ", getGyroRadians());
	motor[leftMotor] = motor[rightMotor] = 0;
	tank0.angle=-getGyroDegrees(gyro)/180.0 * PI + tank0.angle;
}

//Tank will stop on specific Coordinate
void moveToCoordinate(Tank & tank0, Coordinate const & destination)
{
	turnAngle(tank0, angleBetween(tank0.location, destination));
	tank0.location.x = cos(tank0.angle)*drive(distToCoordinate(tank0.location, destination));
	tank0.location.y = sin(tank0.angle)*drive(distToCoordinate(tank0.location, destination));
}

//tank will stop when in range of target
void moveToFiringLocation(Tank & tank0, Coordinate const & target)
{
	turnAngle(tank0,angleBetween(tank0.location, target));
	drive(distToRange(tank0.location, target));
	Coordinate finalLocation;
	finalLocation.x=0;
	finalLocation.y=0;
	findFiringPosition(tank0.location, target, finalLocation);
	tank0.location.x = cos(tank0.angle)*drive(distToCoordinate(tank0.location, target));
	tank0.location.y = sin(tank0.angle)*drive(distToCoordinate(tank0.location, target));
}


void returnHome(Tank & tank0)
{
	Coordinate home;
	home.x=0;
	home.y=0;
	moveToCoordinate(tank0, home);
	turnAngle(tank0, 0);
}

float getGyroRadians()
{
	return degToRad(getGyroDegrees(gyro));
}

float degToRad(float degrees)
{
	return degrees/180*PI;
}

#endif
