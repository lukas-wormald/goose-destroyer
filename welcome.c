//this will be the first function run after the setup
#ifndef WELCOME
#define WELCOME

void beginProgramMenu() //displays the start of the program
{
	displayString(3, "Welcome to GOOSE DESTROYER!");
	displayString(5, "To input file coordinates:");
	displayString(6,  "press the up button");
	displayString(8, "To manually select coordinates");
	displayString(9, "please press the Down Button");
}

//fills the array with the targets
int getTargets(locArr & targets)
{
	int totalTargets = 0;
	TEV3Buttons userInput = buttonNone;

	do
	{
		userInput = getButtonPressed();
	}
	while(userInput != buttonUp && userInput != buttonDown);

	if(userInput == buttonUp)
	{//file coordinates
		TFileHandle finCoords;
		openReadPC(finCoords,"CoordinateTesting.txt");
		totalTargets = readCoordinates(targets, finCoords); //in TankFileRead.c
		closeFilePC(finCoords);
	}
	else
	{//user input screen coordinates
		totalTargets = getMultipleCoordinates(targets); //in inputCoordinates.c
	}
	return totalTargets;
}

#endif
