//TESTED AND WORKS

#include "initialization.c"

#ifndef INPUT_COORDINATES
#define INPUT_COORDINATES


//creates an on-screen menu to select a single point to fire at.
void getCoordinates(Coordinate coord)
{
	//Assume robot starts facing the X+ direction.
	//Left and Right arrows to increment the y value, up down increment the x value
	//EnterButton saves the point.

	int xLoc = 0, yLoc = 0;

	eraseDisplay();
	drawLine(0, HEIGHT/2, WIDTH, HEIGHT/2);//horizontal line
	drawLine(WIDTH/2,0,WIDTH/2+1,HEIGHT);//vertical line
	displayStringAt(0,8,"X=%d  ",xLoc);
	displayStringAt(0,16,"Y=%d  ", yLoc);

	TEV3Buttons buttonPressed = buttonNone;

	do
	{
		buttonPressed = getButtonPressed();

		clearPixel(xLoc+WIDTH/2,yLoc+HEIGHT/2);

		if(buttonPressed == buttonRight)
			yLoc-=10;
		else if (buttonPressed == buttonLeft)
			yLoc+=10;
		else if (buttonPressed == buttonUp)
			xLoc+=10;
		else if (buttonPressed == buttonDown)
			xLoc-=10;
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

int getMultipleCoordinates(locArr & targetLocations)
{
	int numTargets = 0;
	TEV3Buttons buttonPressed = buttonEnter;

	while(buttonPressed == buttonEnter)
	{
		eraseDisplay();
		displayCenteredBigTextLine(3,"Enter Target?");
		displayCenteredTextLine(6,"Center = YES  Other = NO");
		//vertical line offset by 1 so that it is visible on the screen
		//^for some weird reason
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

void showDestinations(locArr const & destinations)
{
	eraseDisplay();
	for(int i = 0; i < MAXNUMTARGETS; i++)
	displayTextLine(i+1, "%f  %f", destinations.locations[i].x, destinations.locations[i].y);
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
