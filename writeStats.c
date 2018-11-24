// commenting complete

#include "PC_FileIO.c"
#ifndef WRITE_STATS
#define WRITE_STATS
/*
Function to output stats to a file:
Function will output total run time of mission, the number of geese shot, the mission status (success or failure),
the amount of ammo remaining, and the total number of targets
*/
void writeStatsToFile(float runTime, int numGeeseShot, string & missionStatus, int ammoRemaining, int totalTargets)
{
	TFileHandle fout;
	bool fileOkay = openWritePC(fout, "stats.txt");
	
	runTime = time1[T1] / 1000; // converts time to seconds
	writeLongPC(fout,runTime);
	writeEndlPC(fout);
	writeLongPC(fout,numGeeseShot);
	writeEndlPC(fout);
	if (ammoRemaining < 8)
	{
		writeTextPC(fout, "Robot needs reloading");
		writeEndlPC(fout);
	}
	else
	{
		writeTextPC(fout, "Robot does not need reloading");
		writeEndlPC(fout);
	}
	if(totalTargets - numGeeseShot == 0)
	{
		missionStatus = "Mission was a Success!";
		writeTextPC(fout, "Mission was a Success!");
		writeEndlPC(fout);
	}
	else
	{
		missionStatus = "Mission was a Failure";
		writeTextPC(fout, "Mission was a Failure");
		writeEndlPC(fout);
	}

	closeFilePC(fout);
}

#endif
