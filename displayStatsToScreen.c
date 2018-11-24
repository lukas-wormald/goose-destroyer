// comenting in progress
#include "initialization.c"
#include "calculateStats.c"

#ifndef STATSTOSCREEN
#define STATSTOSCREEN

// function that displays the mission stats to the screen (same as output file)
void displayStatsToScreen(Stats mission)
{
	//display stats
	eraseDisplay();
	calculateStats(mission);
	displayString(2, "MISSION STATS:");
	//if no bullets were shot
	if (mission.ammoRemaining == 8 && mission.isAttacked == false)
	{
		displayString(4, "No targets were shot");
	}
	else if (mission.ammoRemaining < 8 && mission.needReload == true)
	{
		displayString(4, "Mission took : %d", mission.runTime, "seconds");
		displayString(5, "Need to Reload");
	}
	else if (mission.ammoRemaining == 8 && mission.needReload == false)
	{
		displayString(4, "Mission took : %d", mission.runTime, "seconds");
		displayString(5, "No reloading necessary");
	}

	//
	displayString(3, "Targets Shot: %d", mission.numGeeseShot);

	//mission is a success only if all targets are shot
	if (mission.totalTargets - mission.targetsShot == 0)
		displayString(6, "MISSION: Success!");
	else
		displayString(6, "MISSION: Failure");
}

//Testing main
/*
task main()
{
	int runTime = 0;
	int numGeeseShot = 0;
	bool needReload = true;
	string missionStatus = "";
	int ammoRemaining = 0;

	displayStatsToScreen(runTime,numGeeseShot,needReload,missionStatus,ammoRemaining);
}
*/

#endif
