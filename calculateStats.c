#include "PC_FileIO.c"
#ifndef CALCULATE_STATS
#define CALCULATE_STATS
int ammoRemaining = 0;


void calculateStats(int runTime, int numGeeseShot, string missionStatus, int targetsShot, int totalTargets)

	{

		TFileHandle fout;

		bool fileOkay = openWritePC(fout, "stats.txt");



		runTime = time1[T1] / 1000;

		writeLongPC(fout,runTime);

		writeTextPC(fout, "seconds");

		writeEndlPC(fout);

		numGeeseShot = targetsShot;

		writeLongPC(fout,numGeeseShot);

		writeTextPC(fout, "geese shot");

		writeEndlPC(fout);

		if (ammoRemaining < 8)

			writeTextPC(fout, "Robot needs reloading");

			writeEndlPC(fout);

		if (ammoRemaining == 8)

			writeTextPC(fout, "Robot does not need reloading");

			writeEndlPC(fout);



		if(totalTargets - targetsShot == 0)

			missionStatus = "Mission was a Success!";

			writeTextPC(fout, "Mission was a Success!");

			writeEndlPC(fout);

		if (totalTargets - targetsShot != 0)

			missionStatus = "Mission was a Failure";

			writeTextPC(fout, "Mission was a Failure");

			writeEndlPC(fout);



			closeFilePC(fout);

	}

#endif
