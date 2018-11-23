//final main with all versions of input
#include "initialization.c"
#include "TankFileRead.c"
#include "calculations.c"
#include "tankMovements.c"
#include "fire.c"
#include "calculateStats.c"
#include "gooseCheck.c"
#include "inputCoordinates.c"
#include "welcome.c"

//create struct for all the stats
//include file for the includes
//fix coordinates
//check for goose turn back angle

task main()
{

	setupSensors();
	//Defining Variables
	Tank gooseDestroyer;
	gooseDestroyer.location.x=0;
	gooseDestroyer.location.y=0;
	gooseDestroyer.angle = 0;

	int runTime = 0;
	int numGeeseShot = 0;
	int ammoRemaining = NUMBALLS;
	int totalTargets = 0;
	int targetsShot = 0;
	bool isAttacked = false;
	int outOfRange = 0;
	string missionStatus = "";

	locArr targets;
	setupLocArrStruct(targets);
	beginProgram(); //in welcome.c
	totalTargets = getTargets(targets); //fills the array with targets based on user input

	time1[T1] = 0;
	for(int currentTarget = 0; currentTarget < totalTargets && ammoRemaining > 0 && !isAttacked; currentTarget++)
	{
		//if target is in range, shoot it, and increment counters
		if(targetInRange(gooseDestroyer, targets.locations[currentTarget]))
		{
			moveToFiringLocation(gooseDestroyer, targets.locations[currentTarget], isAttacked);
			shootTheGoose(ammoRemaining, gooseDestroyer, isAttacked);
			targetsShot++;
		}
		else
			outOfRange++;
	}

	returnHome(gooseDestroyer, isAttacked);
	runTime = time1[T1] / 1000;
	//calculateStats(runTime, ammoRemaining, totalTargets, isAttacked, targetsShot, outOfRange);
	calculateStats(runTime, missionStatus, targetsShot, totalTargets, isAttacked, outOfRange);

}
