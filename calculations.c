#include "initialization.c"
#ifndef CALCULATIONS
#define CALCULATIONS
//Calculations
//Distance to closest firing position
float distToRange (Coordinate const & tank0Loc, Coordinate const & target)
{
	return sqrt(pow(tank0Loc.x - target.x, 2) + pow(tank0Loc.y - target.y, 2)) - RANGE;
}

float distToCoordinate (Coordinate const & tank0Loc, Coordinate const & target)
{
	return sqrt(pow(tank0Loc.x - target.x, 2) + pow(tank0Loc.y - target.y, 2));
}

//Angle between tank and target Coordinate in radians
float angleBetween (Coordinate const & tank0Loc, Coordinate const & target)
{
	float delx = target.x - tank0Loc.x;
	float dely = target.y - tank0Loc.y;



	//range of arctan is -PI/2 to PI/2
	if (delx<0)
	{
		return atan(dely / delx) + PI;
	}
	else if (delx>0)
		return atan(dely / delx);
	else if (delx < TOL && dely > 0)
		return PI/2;
	else if (delx < TOL && dely < 0)
		return -PI/2;
	else // no change at all
		return 0;

}

//Coordinate of the closest firing position, used to redefine tank location
void findFiringPosition (Coordinate const & tank0Loc, Coordinate const & target, Coordinate & firingLocation)
{
	firingLocation.x = cos(angleBetween(tank0Loc, target)) * distToRange(tank0Loc, target);
	firingLocation.y = sin(angleBetween(tank0Loc, target)) * distToRange(tank0Loc, target);
}

#endif
