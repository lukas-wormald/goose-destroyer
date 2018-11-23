#include "initialization.c"
#ifndef CALCULATIONS
#define CALCULATIONS
//Calculations

float distToCoordinate(Coordinate const tank0Loc, Coordinate const target)
{
	return sqrt(pow(tank0Loc.x - target.x, 2) + pow(tank0Loc.y - target.y, 2));
}

float distToRange(Coordinate const tank0Loc, Coordinate const target)
{
	return distToCoordinate(tank0Loc, target) - RANGE;
}

bool targetInRange(Tank const tank0, Coordinate const target)
{
	return (distToRange(tank0.location, target) / BOTSPEED < MAXSECONDSRANGE);
}

//Angle between tank and target Coordinate in radians
float angleBetween (Coordinate const & tank0Loc, Coordinate const & target)
{
	float delx = target.x - tank0Loc.x;
	float dely = target.y - tank0Loc.y;
	float angle = 0;
	//range of arctan is -PI/2 to PI/2
	if (delx<0 && dely>=0)
		return atan(dely / delx) + PI;
	else if (abs(delx) < TOL && dely > 0)
		return PI / 2.0;
	else if (abs(delx) < TOL && dely < 0)
		return -(PI / 2.0);
	else if (delx<0 && dely<0)
		return atan(dely / delx) - PI;
	else if (delx>0)
		return atan(dely / delx);
	return 0;
}

float minTankTurn (Tank tank0, float calculatedAngle)
{
	float turn = calculatedAngle - tank0.angle;
	//So it will never turn more than PI
	if(fabs(turn) > PI)
	{
		if(turn<0)
			turn += 2 * PI;
		else
			turn -= 2 * PI;
	}
	return turn;
}
//Coordinate of the closest firing position, used to redefine tank location
void findFiringPosition (Coordinate const & tank0Loc, Coordinate const & target, Coordinate & firingLocation)
{
	firingLocation.x = cos(angleBetween(tank0Loc, target)) * distToRange(tank0Loc, target);
	firingLocation.y = sin(angleBetween(tank0Loc, target)) * distToRange(tank0Loc, target);
}

#endif
