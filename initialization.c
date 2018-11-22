#ifndef INTIALIZATION
#define INTIALIZATION

//Constants
const int MAXNUMTARGETS = 8;
//Avg firing distance of robot
const float RANGE = 20;
const int SPEED = 50;
const int NUMBALLS = 8;
const int FIRESPEED = 100;
const float GEARRADIUS = 2.75;
const float GOOSETOL = 20;
const float TOL = 1*pow(10,-2);
const float BOTSPEED = 1.0/23; //meters / second

//Naming Motors
const tMotor leftMotor = motorA;
const tMotor rightMotor = motorD;
const tMotor hopperMotor = motorB;
const tMotor firingMotor = motorC;

//Naming Sensors
const tSensors gyro = S2;
const tSensors ultraSonic = S3;
const tSensors touch = S4;

//Display Sizes
const int WIDTH = 178;
const int HEIGHT = 128;

// Structs
typedef struct
{
	float x;
	float y;
}Coordinate;

typedef struct
{
	Coordinate locations[MAXNUMTARGETS];
}locArr;

typedef struct
{
	Coordinate location;
	float angle;
}Tank;

//Setup Sensors
//sets up the touch, ultrasonic, and gyro sensors
void setupSensors()
{
	SensorType[touch] = sensorEV3_Touch;
	SensorType[ultraSonic] = sensorEV3_Ultrasonic;
	SensorType[gyro] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[gyro] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
	//wait for robot to be still in order to reset the gyro
	//while(getGyroRate(gyro) != 0)
	//{}
	//resetGyro(gyro);
}

void setupLocArrStruct(locArr & setupStruct)
{
	for(int index = 0; index < MAXNUMTARGETS; index++)
	{
		setupStruct.locations[index].x = 0;
		setupStruct.locations[index].y = 0;
	}
}

TEV3Buttons getButtonPressed()
{
    TEV3Buttons buttonPressed = buttonNone;
    while(!getButtonPress(buttonAny))
    {} //wait for a button to be pressed
    if(getButtonPress(buttonUp))
        buttonPressed = buttonUp;
    else if (getButtonPress(buttonDown))
        buttonPressed = buttonDown;
    else if (getButtonPress(buttonLeft))
        buttonPressed = buttonLeft;
    else if (getButtonPress(buttonRight))
        buttonPressed = buttonRight;
    else if (getButtonPress(buttonEnter))
        buttonPressed = buttonEnter;
    while (getButtonPress(buttonAny))
    {} //wait for button release
    return buttonPressed;
}

#endif
