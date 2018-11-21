// function to read in coordinates from a file - these will all be in cm
#include "PC_FileIO.c"
#include "initialization.c"

#ifndef TANK_FILE_READ
#define TANK_FILE_READ

int readCoordinates(locArr locs, TFileHandle fin)
{
	int numTargets = 0; //-1 in MAXNUMTARGETS for some wierd reason??
	while(readFloatPC(fin, locs.locations[numTargets].x) && readFloatPC(fin, locs.locations[numTargets].y) && numTargets < MAXNUMTARGETS-1)
		numTargets++;
	return numTargets;
}

#endif
