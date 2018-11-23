//final main with all versions of input
#include "includes.c"

//fix coordinates
//check for goose turn back angle - this will require a little more reworking

task main()
{

	setupSensors();
	//Defining Variables
	Tank gooseDestroyer;
	initializeTank(gooseDestroyer);

	locArr targets;
	initializeLocArrStruct(targets);

	Stats mission;
	initializeStats(mission);

	beginProgramMenu(); //in welcome.c
	mission.totalTargets = getTargets(targets); //fills the array with targets based on user input

	time1[T1] = 0;
	for(int currentTarget = 0; currentTarget < mission.totalTargets && mission.ammoRemaining > 0 && !mission.isAttacked; currentTarget++)
	{
		//if target is in range, shoot it, and increment counters
		if(targetInRange(gooseDestroyer, targets.locations[currentTarget]))
		{
			moveToFiringLocation(gooseDestroyer, targets.locations[currentTarget], mission.isAttacked);
			shootTheGoose(mission.ammoRemaining, gooseDestroyer, mission.isAttacked);
			mission.targetsShot++;
		}
		else
			mission.outOfRange++;
	}

	returnHome(gooseDestroyer, mission.isAttacked);
	//mission.runTime = time1[T1] / 1000; //this is taken care of in calculate stats
	//calculateStats(runTime, missionStatus, targetsShot, totalTargets, isAttacked, outOfRange);
	calculateStats(mission);
}
