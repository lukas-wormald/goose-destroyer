#ifndef INTIALIZATION
#define INTIALIZATION

//Constants
const int MAXNUMTARGETS = 8;
//Avg firing distance of robot
const float RANGE = 55; //distance the the robot will shoot
const float OFFSETANGLE = 18;//degrees CCW, the offset that the ball shoots from the center of the bot
const int SPEED = -55; //because motors mounted backwards
const int TURNSPEED = SPEED;
const int NUMBALLS = 8; //number of balls that the tank starts with
const int FIRESPEED = 100;
const int HOPPERSPEED = 5;
const float GEARRADIUS = 2.52; //calculated based on distance traveled with currently set gear radius
const int GOOSETOL = 20;
const float TOL = 1*pow(10,-2); //tolerance used for comparing floats

//Range constants
const float BOTSPEED = 100/4.9; //centimeters / second used to calculate shots out of range
const int MAXSECONDSRANGE = 5*60; //5 minutes

//Naming Motors
const tMotor leftMotor = motorA; //large in tracks
const tMotor rightMotor = motorD; //large in tracks
const tMotor hopperMotor = motorB; //EV3 medium
const tMotor firingMotor = motorC; //NXT large

//Naming Sensors
const tSensors touch1 = S1;
//const tSensors touch2 = S2;
const tSensors ultraSonic = S3;
const tSensors gyro = S4;

//Display Sizes
const int WIDTH = 178;
const int HEIGHT = 128;

//Notes on timers
//T1 used for mission timing
//T2 used for waiting for goose checking

// Structs

//Stores an X and Y value that represent the location of the tank on a standard cartesian plane, in cm
typedef struct
{
	float x;
	float y;
}Coordinate;

void initializeCoordinate(Coordinate coord)
{
	coord.x = 0;
	coord.y = 0;
}

//Stores an array of coordinates that will represent all the targets that must be hit
typedef struct
{
	Coordinate locations[MAXNUMTARGETS];
}locArr;

//tank position data
//a coordinate in cm, and an angle from +x axis that the tank is currently facing, if it were at the origin
typedef struct
{
	Coordinate location;
	float angle;
}Tank;

void initializeTank(Tank tank)
{
	tank.angle = 0;
	initializeCoordinate(tank.location);
}

typedef struct
{
	int runTime;
	int numGeeseShot;
	int ammoRemaining;
	bool needReload;
	int totalTargets;
	int targetsShot;
	bool isAttacked;
	int outOfRange;
	string missionStatus;
}Stats;

void initializeStats(Stats data)
{
		data.runTime = 0;
		data.numGeeseShot = 0;
		data.ammoRemaining = NUMBALLS;
		data.needReload = false;
		data.totalTargets = 0;
		data.targetsShot = 0;
		data.isAttacked = false;
		data.outOfRange = 0;
		data.missionStatus = "";
}

//Setup Sensors
//sets up the touch, ultrasonic, and gyro sensors
void setupSensors()
{
	SensorType[touch1] = sensorEV3_Touch;
	//SensorType[touch2] = sensorEV3_Touch;
	SensorType[ultraSonic] = sensorEV3_Ultrasonic;
	SensorType[gyro] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[gyro] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);
	//wait for robot to be still in order to reset the gyro
	while(getGyroRate(gyro) != 0)
	{}
	resetGyro(gyro);
	wait1Msec(50);
}

//initialize the targets array that is wrapped in a struct
void initializeLocArrStruct(locArr & setupStruct)
{
	for(int index = 0; index < MAXNUMTARGETS; index++)
	{
		setupStruct.locations[index].x = 0;
		setupStruct.locations[index].y = 0;
	}
}

//waits for a button to be pressed and returns that button
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
