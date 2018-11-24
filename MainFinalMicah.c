//final main with all versions of input
#include "includes.c"

//fix coordinates - get proper calculations file!!
//check for goose turn back angle - this will require a little more reworking, not tested yet

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
			shootTheGoose(mission, gooseDestroyer);
			mission.targetsShot++;
		}
		else
			mission.outOfRange++;
	}

	if(mission.isAttacked && mission.ammoRemaining > 0)
		defend(gooseDestroyer, mission);

	returnHome(gooseDestroyer, mission.isAttacked);
	calculateStats(mission);
}
