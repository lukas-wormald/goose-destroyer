//commenting complete

//include all the relevant files
#include "includes.c"

task main()
{
	//Setup all sensors, structs, and variables
	setupSensors();
	Tank gooseDestroyer;
	initializeTank(gooseDestroyer);
	locArr targets;
	initializeLocArrStruct(targets);
	Stats mission;
	initializeStats(mission);
	beginProgramMenu(); //in welcome.c
	mission.totalTargets = getTargets(targets); //fills the array with targets based on user input
	time1[missionTimer] = 0;
	
	//loop through all the targets, and shoot them if possible
	for(int currentTarget = 0; currentTarget < mission.totalTargets && mission.ammoRemaining > 0 && !mission.isAttacked; currentTarget++)
	{
		//if target is in range (time limit defined in initialization), shoot it, and increment relevant counters
		if(targetInRange(gooseDestroyer, targets.locations[currentTarget]))//targetInRange is in calculations.c
		{
			moveToFiringLocation(gooseDestroyer, targets.locations[currentTarget], mission.isAttacked);//in tankMovements.c
			shootTheGoose(mission, gooseDestroyer);//in gooseCheck.c
			mission.targetsShot++;
		}
		//if the target was out of range, then skip it, and increment the counter
		else
			mission.outOfRange++;
	}
	
	//if the tank was attacked, defend itself
	if(mission.isAttacked && mission.ammoRemaining > 0)
		defend(gooseDestroyer, mission);//in defense.c
	
	//end the mission by returning to the home position
	//calculate the stats and write them to a file
	returnHome(gooseDestroyer, mission.isAttacked);//in tankMovements.c
	calculateStats(mission);
}
