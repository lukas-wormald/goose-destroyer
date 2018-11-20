int beginProgram()
{
	displayString(3, "Welcome to GOOSE DESTROYER!");
	displayString(5, "To input file coordinates:");
	displayString(6,  "press the up button");
	displayString(8, "To manually select coordinates");
	displayString(9, "please press the Down Button");

	TEV3Buttons buttonPressed = getButtonPressed();
	if ((buttonPressed) == buttonUp)
	{
		//readCoordinates();
	}

	else if (buttonPressed == buttonDown)
	{
		//manuallySelectCoordinatesFunction();
	}

}




task main()
{

}
