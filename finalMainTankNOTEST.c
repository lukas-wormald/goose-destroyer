//Currently being used to test

#include "initialization.c"
#include "TankFileRead.c"
#include "calculations.c"
#include "tankMovements.c"
#include "fire.c"
#include "calculateStats.c"
#include "gooseCheck.c"
//IF WE HAVE TIME #include "attacked.c"

//#include "inputCoordinates.c"


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
	int ammoRemaining = 0;
	string missionStatus = "";
	int totalTargets = 0;
	bool isAttacked = false;
	int outOfRange = 0;

	Coordinate oldBot;
	oldBot.x=0;
	oldBot.y=0;


	locArr locationsAtIndex;
	for(int i = 0; i < MAXNUMTARGETS; i++)
	{
		locationsAtIndex.locations[i].x = 0;
		locationsAtIndex.locations[i].y = 0;
	}

	//READING FILES
	TFileHandle finCoords;
	openReadPC(finCoords,"CoordinateTesting.txt");
	totalTargets = readCoordinates(locationsAtIndex, finCoords);
	closeFilePC(finCoords);




	time1[T1]=0;
	int currentTarget = 0;
	while(currentTarget < totalTargets)
	{
		displayString(1,"STARTED");
		TEV3Buttons buttonPressed = getButtonPressed();

		if(buttonPressed == buttonEnter)
		{
			oldBot.x=gooseDestroyer.location.x;
			oldBot.y=gooseDestroyer.location.y;

			displayString(4, "Old Bot: %d, %d       ", gooseDestroyer.location.x, gooseDestroyer.location.y);
			displayString(5, "Target: %d, %d       ", locationsAtIndex.locations[currentTarget].x, locationsAtIndex.locations[currentTarget].y);

			//Will only go to a target if it is in range
			if(distToRange(gooseDestroyer.location, locationsAtIndex.locations[currentTarget]) / BOTSPEED < 5 * 60)
			{
				moveToFiringLocation(gooseDestroyer, locationsAtIndex.locations[currentTarget], isAttacked);
				shootTheGoose(ammoRemaining, gooseDestroyer, isAttacked);
				//targetsShot = currentTarget+1;
			}
			else
				outOfRange++;
			currentTarget++;

			displayString (8, "Current Location: %d, %d        ", gooseDestroyer.location.x, gooseDestroyer.location.y);
		}
	}
	//TESTING DONE

	//WHAT WE ACTUALLY WANT
	//STRETCH find how to check if attacked

	//starting to move out and shoot targets
	//for keeping track of total mission time
	time1[T1] = 0;
	int targetsShot = 0;
	for(int currentTarget = 0; currentTarget<totalTargets && ammoRemaining >= 1 && !isAttacked; currentTarget++)
	{
		//Will only go to a target if it is in range
		if(distToRange(gooseDestroyer.location, locationsAtIndex.locations[currentTarget]) / BOTSPEED < 5 * 60)
		{
			moveToFiringLocation(gooseDestroyer, locationsAtIndex.locations[currentTarget], isAttacked);
			shootTheGoose(ammoRemaining, gooseDestroyer, isAttacked);
			targetsShot = currentTarget+1;
		}
		else
			outOfRange++;
	}

	returnHome(gooseDestroyer, isAttacked);

	float totalTime = time1[T1] / 1000;

	calculateStats(totalTime, missionStatus, ammoRemaining, totalTargets, isAttacked, outOfRange);
}
