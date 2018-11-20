#include "initialization.c"
#include "TankFileRead.c"
#include "calculations.c"
#include "moveAndCheck.c"
#include "fire.c"
#include "writeStats.c"
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
//TESTING
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
			displayString(4, "Old Bot: %d, %d", gooseDestroyer.location.x, gooseDestroyer.location.y);
			displayString(5, "Target: %d, %d       ", locationsAtIndex.locations[currentTarget].x, locationsAtIndex.locations[currentTarget].y);

			moveToCoordinate(gooseDestroyer, locationsAtIndex.locations[currentTarget]);
			currentTarget ++;
		}
	}
//TESTING DONE

	//WHAT WE ACTUALLY WANT
	//STRETCH find how to check if attacked

	//starting to move out and shoot targets
	//for keeping track of total mission time
	//time1[T1] = 0;
	//int targetsShot = 0;
	//for(int currentTarget = 0; currentTarget<totalTargets && ammo >= 1)
	//{
	//	moveToFireLocation(gooseDestroyer, targetLocation);
	//	shootTheGoose(ammoRemaining, gooseDestroyer);
	//	targetsShot = currentTarget+1;
	//}

	//gooseDestroyer.returnHome();

	float totalTime = time1[T1] / 1000;

	writeStatsToFile(totalTime, numGeeseShot, missionStatus, ammoRemaining, totalTargets);
}
