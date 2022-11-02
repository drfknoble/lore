/*
*	ROBOT.h - Libary for controlling the Low-Cost Open-Source Robotic Education (LORE) kit.
*	Version 1.1.
*	Copyright (c) 2014 Dr. Frazer K. Noble. All rights reserved.
*
*	Low-cost Open-source Robotics Educational (LORE) kits are provided "as is" with no warranties whatsoever,
* 	including any warranty of merchantability, non - infringement, fitness for any particular purpose,
* 	or any warranty otherwise arising out of any proposal, specification or sample.
* 	LORE kits (and manufacturers and distributors) disclaim all liability, including liability for infringement of any proprietary rights,
*	relating to use of information in any documents and files and software and no license, express or implied, by LORE kits or otherwise,
*	to any intellectual property rights is granted herein. LORE kits(and manufacturers and distributors) assumes no responsibility or liability
*	for any errors or inaccuracies that may appear in any documentation or files or any software that may be provided.
*	The information in any documents or files is furnished for informational use only, is subject to change without notice,
*	and should not be construed as a commitment by LORE kits(and manufacturers and distributors).
*/

/*
*	The LORE robot is controlled by the following functions.
*
*	The functions are:
*
*	initialise()				- Initialises the LORE robot's pins' states (LOW/HIGH) and direction (INPUT/OUTPUT).
*	move(int direction)			- Moves the robot in the desired direction (LEFT, RIGHT, FORWARD, BACKWARD).
*	readSensor(int sensor)		- Takes a measurement from a sensor (FRONT_SENSOR, LEFT_SENSOR, RIGHT_SENSOR)
*								  and returns the distanc measured.
*	buttonPressed(int button)	- Checks to see if the a button (PROGRAM, SELECT, LEFT, RIGHT, FORWARD, BACKWARD)
*								  is pressed.
*	writeLCD(char* string)		- Writes a series of characters to the LORE robot's LCD panel.
*
*/

#ifndef ROBOT_h
#define ROBOT_h

/*
 *	Defines for the LORE robot used with the ROBOT library.
 */

//	Button #defines

#define BACKWARD 7
#define FORWARD 8
#define RIGHT 9
#define LEFT 10
#define SELECT 11
#define PROGRAM 12

// LCD #defines

#define RS A0
#define E A1
#define D4 A2
#define D5 A3
#define D6 A4
#define D7 A5

//	Sensor #defines

#define FRONT_SENSOR 2
#define LEFT_SENSOR 3
#define RIGHT_SENSOR 4

//	Motor #defines

#define LEFT_MOTORS 5
#define RIGHT_MOTORS 6

//	Functions 


class ROBOT {

public:

	ROBOT();

	bool initialise();

	bool buttonPressed(int button);
	bool clear();
	bool move(int direction);
	bool turn(int direction);
	bool program(int direction);
	bool run();
	bool writeLCD(char* string);
	long measureDistance(int sensor);
	bool setTurnTime(int direction, int time);

private:

	int leftTurnTime;
	int rightTurnTime;

	long programDebounceTime;
	bool programState;
	bool programPrevState;

	long selectDebounceTime;
	bool selectState;
	bool selectPrevState;

	long leftDebounceTime;
	bool leftState;
	bool leftPrevState;

	long rightDebounceTime;
	bool rightState;
	bool rightPrevState;

	long forwardDebounceTime;
	bool forwardState;
	bool forwardPrevState;

	long backwardDebounceTime;
	bool backwardState;
	bool backwardPrevState;

	long frontSensorValue;
	long leftSensorValue;
	long rightSensorValue;

	long debounceDelay;

	char programString[50];
	int programSet;
	int programSize;

	bool readButton(int button, bool &buttonState, bool &buttonPrevState, long &debounceTime);
	bool readSensor(int sensor, long &distance);

};

#endif

