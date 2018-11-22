#include "initialization.c"
#include "calculations.c"
#include "attacked.c"
#ifndef TANK_MOVEMENTS
#define TANK_MOVEMENTS

//Tank Movements
//TANK MOTION
//driveForward set distance

float degToRad(float degrees)
{
	return degrees/180*PI;
}

float getGyroRadians()
{
	return degToRad(getGyroDegrees(gyro));
}

void drive (float distance, bool & isAttacked) //TESTED Can Drive set distances
{
	nMotorEncoder[leftMotor] = 0;
	int direction = 1; // going forward
	if (distance<0)
		direction = -1;
	motor[leftMotor] = motor[rightMotor] = direction * SPEED; //Needs to be negative to go forward
	while(direction * (-nMotorEncoder[leftMotor] / 360.0 * GEARRADIUS * 2 * PI) < direction * distance )
	{
		isAttacked = attacked();
	}
	motor[leftMotor] = motor[rightMotor] = 0;
}

void turnAngle (Tank & tank0, float rotation, bool & isAttacked)  //TESTED  WORKS BEST WHEN SLOWER SPEED
{
	//1 counter clockwise
	float turn = minTankTurn(tank0, rotation);
	int direction = 1;
	if (turn<0)
	{
		//turn clockwise
		direction = -1;
	}
	//default is counter clockwise
	motor[leftMotor] = - direction * TURNSPEED;
	motor[rightMotor] = direction * TURNSPEED;
	resetGyro(gyro);
	wait1Msec(20);
	displayString(2, "Direction: %f       ", turn);
	while(direction*turn > direction * -getGyroRadians())
	{
		isAttacked = attacked();
	}
	motor[leftMotor] = motor[rightMotor] = 0;
	displayString(3, "Gyro: %f       ", -getGyroRadians());
	tank0.angle=turn;
}

//Tank will stop on specific Coordinate
void moveToCoordinate(Tank & tank0, Coordinate const & destination, bool & isAttacked)
{
	displayString(8, "Old Angle: %f", tank0.angle);
	turnAngle(tank0, angleBetween(tank0.location, destination), isAttacked);
	drive(distToCoordinate(tank0.location, destination), isAttacked);
	displayString(9, "New Angle: %f", tank0.angle);
	tank0.location.x = destination.x;
	tank0.location.y = destination.y;
}

//tank will stop when in range of target
void moveToFiringLocation(Tank & tank0, Coordinate const & target, bool & isAttacked)
{
	turnAngle(tank0,angleBetween(tank0.location, target), isAttacked);
	drive(distToRange(tank0.location, target), isAttacked);
	turnAngle(tank0, tank0.angle-degToRad(OFFSETANGLE), isAttacked); //compensate for consistently angled firing
	Coordinate finalLocation;
	finalLocation.x=0;
	finalLocation.y=0;
	findFiringPosition(tank0.location, target, finalLocation);
	tank0.location.x = finalLocation.x;
	tank0.location.y = finalLocation.y;
}


void returnHome(Tank & tank0, bool & isAttacked)
{
	Coordinate home;
	home.x=0;
	home.y=0;
	moveToCoordinate(tank0, home, isAttacked);
	turnAngle(tank0, 0, isAttacked);
}


#endif
