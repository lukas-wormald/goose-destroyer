#include "initialization.c"
#ifndef CALCULATIONS
#define CALCULATIONS
//Calculations


//Distance to specific point
float distToCoordinate (Coordinate const & tank0Loc, Coordinate const & target)
{
	//Using Pythagoras
	return sqrt(pow(tank0Loc.x - target.x, 2) + pow(tank0Loc.y - target.y, 2));
}


//Distance to closest firing position
float distToRange (Coordinate const & tank0Loc, Coordinate const & target)
{
	//Using Pythagoras - the range
	return distToCoordinate(tank0Loc, target) - RANGE;
}

//Finds if the target is too far away
bool targetInRange(Tank const tank0, Coordinate const target)
{
	//distance div time < max travel time
	return (distToRange(tank0.location, target) / BOTSPEED < MAXSECONDSRANGE);
}

//Angle between tank and target Coordinate in radians
float angleBetween (Coordinate const & tank0Loc, Coordinate const & target)
{
	float delx = target.x - tank0Loc.x;
	float dely = target.y - tank0Loc.y;
	//range of arctan is -PI/2 to PI/2
	if (delx<0 && dely>=0)
		return atan(dely / delx) + PI;
	else if (abs(delx) < TOL && dely > 0)
		return PI / 2.0;
	else if (abs(delx) < TOL && dely < 0)
		return -(PI / 2.0); //For some reason robot C could not understand -PI / 2.0 so it needed brackets
	else if (delx<0 && dely<0)
		return atan(dely / delx) - PI;
	else if (delx>0)
		return atan(dely / delx);
	return 0;
}


//Coordinate of the closest firing position, used to redefine tank location
void findFiringPosition (Coordinate const & tank0Loc, Coordinate const & target, Coordinate & firingLocation)
{
	firingLocation.x = cos(angleBetween(tank0Loc, target)) * distToRange(tank0Loc, target);
	firingLocation.y = sin(angleBetween(tank0Loc, target)) * distToRange(tank0Loc, target);
}

#endif
