bool gooseAttack = true;
int totalTargets = 0;
int targetsShot = 0;

void displayStatsToScreen(int runTime, int numGeeseShot, bool needReload, string missionStatus, int ammoRemaining)
{
	//display stats
	eraseDisplay();
	calculateStats();
	displayString(2, "MISSION STATS:");
	//if no bullets were shot
	if (ammoRemaining == 8 && gooseAttack == false)
	{
		displayString(4, "No targets were shot");
	}
	else if (ammoRemaining < 8 && needReload == true)
	{
		displayString(4, "Mission took : %d", runTime, "seconds");
		displayString(5, "Need to Reload");
	}
	else if (ammoRemaining == 8 && needReload == false)
	{
		displayString(4, "Mission took : %d", runTime, "seconds");
		displayString(5, "No reloading necessary");
	}

	//
	displayString(3, "Targets Shot: %d", numGeeseShot);

	//mission is a success only if all targets are shot
	if (totalTargets - targetsShot == 0)
		displayString(6, "MISSION: Success!");
	else
		displayString(6, "MISSION: Failure");
}


task main()
{
	int runTime = 0;
	int numGeeseShot = 0;
	bool needReload = true;
	string missionStatus = "";
	int ammoRemaining = 0;

	displayStatsToScreen(runTime,numGeeseShot,needReload,missionStatus,ammoRemaining);
}
