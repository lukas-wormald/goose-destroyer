//TESTED AND WORKS
//Commenting complete

#include "initialization.c"

#ifndef INPUT_COORDINATES
#define INPUT_COORDINATES

//creates an on-screen menu to select a single point to fire at.
void getCoordinates(Coordinate & coord)
{
	//Assume robot starts facing the X+ direction.
	//Left and Right arrows to increment the x value, up down increment the y value
	//EnterButton saves the point.

	int xLoc = 0, yLoc = 0;
	
	//displays a grid and and X Y locations on the screen
	eraseDisplay();
	drawLine(0, HEIGHT/2, WIDTH, HEIGHT/2);//horizontal line
	drawLine(WIDTH/2,0,WIDTH/2+1,HEIGHT);//vertical line offset by 1 to make it visible, otherwise does not show
	displayStringAt(0,8,"X=%d  ",xLoc);
	displayStringAt(0,16,"Y=%d  ", yLoc);

	//Increment locations with button pushes, and move a pixels
	TEV3Buttons buttonPressed = buttonNone;
	do
	{
		buttonPressed = getButtonPressed();
		clearPixel(xLoc+WIDTH/2,yLoc+HEIGHT/2);
		if(buttonPressed == buttonRight)
			xLoc+=10;
		else if (buttonPressed == buttonLeft)
			xLoc-=10;
		else if (buttonPressed == buttonUp)
			yLoc+=10;
		else if (buttonPressed == buttonDown)
			yLoc-=10;
		if(buttonPressed != buttonEnter)
		{
			setPixel(xLoc+WIDTH/2,yLoc+HEIGHT/2);
			displayStringAt(0,8,"X=%d  ",xLoc);
			displayStringAt(0,16,"Y=%d  ",yLoc);
		}
	}while (buttonPressed != buttonEnter);

	coord.x = xLoc;
	coord.y = yLoc;
}

//fills an array of locations with locations selected by the above function
//returns the number of targets entered
int getMultipleCoordinates(locArr & targetLocations)
{
	int numTargets = 0;
	TEV3Buttons buttonPressed = buttonEnter;

	while(buttonPressed == buttonEnter)
	{
		eraseDisplay();
		displayCenteredBigTextLine(3,"Enter Target?");
		displayCenteredTextLine(6,"Center = YES  Other = NO");

		buttonPressed = getButtonPressed();
		if(buttonPressed == buttonEnter)
		{
			getCoordinates(targetLocations.locations[numTargets]);
			numTargets++;
		}
	}

	eraseDisplay();
	return numTargets;
}

//Displays the locations selected by the on screen menu in order to verify the entries, used for testing only
void showDestinations(locArr const & destinations)
{
	eraseDisplay();
	for(int index = 0; index < MAXNUMTARGETS; index++)
	displayTextLine(index+1, "%f  %f", destinations.locations[index].x, destinations.locations[index].y);
}


//testing main for these functions - All work!
/*
task main()
{
	locArr destinations;
	setupLocArrStruct(destinations);//initializes all values to 0,0
	getMultipleCoordinates(destinations);
	showDestinations(destinations);
	wait1Msec(5000);
}
*/
#endif
