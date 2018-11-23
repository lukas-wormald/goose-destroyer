#include "initialization.c"
#include "calculations.c"
#include "attacked.c"
#ifndef TANK_MOVEMENTS
#define TANK_MOVEMENTS

#define CW -1
#define CCW 1

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

//GOOD
void drive (float distance, bool & isAttacked) //TESTED Can Drive set distances
{
	nMotorEncoder[leftMotor] = 0;
	int direction = 1; // going forward
	if (distance<0) //if should be going backwards, make dir negative
		direction = -1;
	motor[leftMotor] = motor[rightMotor] = direction * SPEED;
	while(direction * (-nMotorEncoder[leftMotor] / 180.0 * GEARRADIUS * PI) < direction * distance)// negative motor encoder because going backwards
	{//direction * will make this always a positive comparison
		isAttacked = attacked(isAttacked);
	}
	motor[leftMotor] = motor[rightMotor] = 0;
}

void turnAngle (Tank & tank0, float rotation, bool & isAttacked)  //TESTED  WORKS BEST WHEN SLOWER SPEED, HIGHER SPEED FOR TREADS
{
	float turn = minTankTurn(tank0, rotation);
	int direction = CCW;
	if (turn<0)
		direction = CW;
	resetGyro(gyro);
	wait1Msec(20);
	motor[leftMotor] = - direction * TURNSPEED;
	motor[rightMotor] = direction * TURNSPEED;
	displayString(2, "Direction: %f       ", turn);
	while(direction*turn > direction * -getGyroRadians())
	{
		isAttacked = attacked(isAttacked);
	}
	motor[leftMotor] = motor[rightMotor] = 0;
	displayString(3, "Gyro: %f       ", -getGyroRadians());
	tank0.angle=turn;
}

//Tank will stop on specific Coordinate
void moveToCoordinate(Tank & tank0, Coordinate const & destination, bool & isAttacked)
{
	turnAngle(tank0, angleBetween(tank0.location, destination), isAttacked);
	drive(distToCoordinate(tank0.location, destination), isAttacked);
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
	initializeCoordinate(finalLocation);
	findFiringPosition(tank0.location, target, finalLocation);
	tank0.location.x += finalLocation.x;
	tank0.location.y += finalLocation.y;
}

void returnHome(Tank & tank0, bool & isAttacked)
{
	Coordinate home;
	initializeCoordinate(home);
	moveToCoordinate(tank0, home, isAttacked);
	turnAngle(tank0, 0, isAttacked);
}


#endif
