#include "PC_FileIO.c"
#include "initialization.c"
#ifndef CALCULATE_STATS
#define CALCULATE_STATS

int ammoRemaining = 0;

void calculateStats(Stats mission)
{

	TFileHandle fout;
	bool fileOkay = openWritePC(fout, "stats.txt");
	
	//if there are not NUMBALLS, tank needs reloading
	mission.needReload = (mission.ammoRemaining < NUMBALLS);

	//how long the mission took
	mission.runTime = time1[missionTimer] / 1000;
	writeLongPC(fout,mission.runTime);
	writeTextPC(fout, " seconds");
	writeEndlPC(fout);

	//how many geese shot
	writeLongPC(fout, mission.targetsShot);
	writeTextPC(fout, " geese shot");
	writeEndlPC(fout);

	//how many targets are out of range
	writeTextPC(fout, "Targets out of range: ");
	writeLongPC(fout, mission.outOfRange);
	writeEndlPC(fout);

	//writes if it needs to be reloaded
	if (mission.needReload)
		writeTextPC(fout, "Robot needs reloading");
	else if (mission.needReload)
		writeTextPC(fout, "Robot does not need reloading");
	writeEndlPC(fout);

	//Failed the mission
	if (mission.isAttacked)
		mission.missionStatus = "Mission was a Failure, Attacked by Goose";
	else if(mission.totalTargets - mission.targetsShot == 0)
		mission.missionStatus = "Mission was a Success!";
	else
		mission.missionStatus = "Mission was a Failure, Not all targets Shot";
	writeTextPC(fout, mission.missionStatus);
	writeEndlPC(fout);

	closeFilePC(fout);

}

#endif
