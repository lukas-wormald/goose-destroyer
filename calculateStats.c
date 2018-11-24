#include "PC_FileIO.c"
#include "initialization.c"
#ifndef CALCULATE_STATS
#define CALCULATE_STATS

int ammoRemaining = 0;

//void calculateStats(int runTime, string missionStatus, int targetsShot, int totalTargets, bool isAttacked, int outOfRange)
void calculateStats(Stats mission)
{

	TFileHandle fout;
	bool fileOkay = openWritePC(fout, "stats.txt");

	mission.needReload = (mission.ammoRemaining < NUMBALLS);

	mission.runTime = time1[T1] / 1000;
	writeLongPC(fout,mission.runTime);
	writeTextPC(fout, " seconds");
	writeEndlPC(fout);

	writeLongPC(fout, mission.targetsShot);
	writeTextPC(fout, " geese shot");
	writeEndlPC(fout);

	writeTextPC(fout, "Targets out of range: ");
	writeLongPC(fout, mission.outOfRange);
	writeEndlPC(fout);

	if (mission.ammoRemaining < 8)
		writeTextPC(fout, "Robot needs reloading");
	else if (mission.ammoRemaining >= 8)
		writeTextPC(fout, "Robot does not need reloading");
	writeEndlPC(fout);

	if (mission.isAttacked)
		mission.missionStatus = "Mission was a Failure";
	else if(mission.totalTargets - mission.targetsShot == 0)
		mission.missionStatus = "Mission was a Success!";
	else
		mission.missionStatus = "Mission was a Failure";
	writeTextPC(fout, mission.missionStatus);
	writeEndlPC(fout);

	closeFilePC(fout);

}

#endif
