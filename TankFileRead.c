//commenting complete
#include "PC_FileIO.c"
#include "initialization.c"

#ifndef TANK_FILE_READ
#define TANK_FILE_READ

//reads coordinates in from a file and loads them into the location array
//returns the number of targets read in
//assumes that the only things in the file are floats
int readCoordinates(locArr & targets, TFileHandle & fin)
{
	int numTargets = 0;
	while(readFloatPC(fin, targets.locations[numTargets].x) && 
	      readFloatPC(fin, targets.locations[numTargets].y) && 
	      numTargets < MAXNUMTARGETS-1)
		numTargets++;
	return numTargets;
}

#endif
