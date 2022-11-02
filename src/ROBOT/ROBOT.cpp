/*
*	ROBOT.cpp - Libary for controlling the Low-Cost Open-Source Robotic Education (LORE) kit.
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

#include "ROBOT.h"
#include "string.h"
#include "Arduino.h"		//	Include Arduino.h to gain access to pin and logic level #defines.
#include "Servo.h"			//	Include Servo.h for controlling the LORE robot motors.
#include "LiquidCrystal.h"	//	Include LiquidCrystal.h to be able to write to LORE robot LCD panel.

LiquidCrystal LCD(RS, E, D4, D5, D6, D7);	//	Create an instance of LiquidCrystal Class. Constructor parameters set data pins.
Servo robotLeftMotors, robotRightMotors;	//	Create instances of Servo class. Objects correspond to LORE robot left and right motors.

ROBOT::ROBOT() {

	leftTurnTime = 900;
	rightTurnTime = 900;

	programDebounceTime = 0;
	programState = HIGH;
	programPrevState = HIGH;

	selectDebounceTime = 0;
	selectState = HIGH;
	selectPrevState = HIGH;

	leftDebounceTime = 0;
	leftState = HIGH;
	leftPrevState = HIGH;

	rightDebounceTime = 0;
	rightState = HIGH;
	rightPrevState = HIGH;

	forwardDebounceTime = 0;
	forwardState = HIGH;
	forwardPrevState = HIGH;
	
	backwardDebounceTime = 0;
	backwardState = HIGH;
	backwardPrevState = HIGH;

	frontSensorValue = 1000;
	leftSensorValue = 1000;
	rightSensorValue = 1000;

	debounceDelay = 50;

	programString[50] = 0;
	programSet = 0;
	programSize = 0;

}

bool ROBOT::initialise() {

	pinMode(PROGRAM, INPUT);
	digitalWrite(PROGRAM, HIGH);

	pinMode(SELECT, INPUT);
	digitalWrite(SELECT, HIGH);

	pinMode(LEFT, INPUT);
	digitalWrite(LEFT, HIGH);

	pinMode(RIGHT, INPUT);
	digitalWrite(RIGHT, HIGH);

	pinMode(FORWARD, INPUT);
	digitalWrite(FORWARD, HIGH);

	pinMode(BACKWARD, INPUT);
	digitalWrite(BACKWARD, HIGH);

	robotLeftMotors.attach(LEFT_MOTORS);
	if (robotLeftMotors.attached()) {
		robotLeftMotors.write(127);
	}

	robotRightMotors.attach(RIGHT_MOTORS);
	if (robotRightMotors.attached()) {
		robotRightMotors.write(127);
	}

	return true;

}


bool ROBOT::buttonPressed(int button) {

	if (button == PROGRAM) {

		if (readButton(PROGRAM, programState, programPrevState, programDebounceTime)) {
			return true;
		}

		return false;

	}

	if (button == SELECT) {

		if (readButton(SELECT, selectState, selectPrevState, selectDebounceTime)) {
			return true;
		}

		return false;

	}

	if (button == LEFT) {

		if (readButton(LEFT, leftState, leftPrevState, leftDebounceTime)) {
			return true;
		}

		return false;

	}

	if (button == RIGHT) {

		if (readButton(RIGHT, rightState, rightPrevState, rightDebounceTime)) {
			return true;
		}

		return false;

	}

	if (button == FORWARD) {

		if (readButton(FORWARD, forwardState, forwardPrevState, forwardDebounceTime)) {
			return true;
		}

		return false;

	}

	if (button == BACKWARD) {

		if (readButton(BACKWARD, backwardState, backwardPrevState, backwardDebounceTime)) {
			return true;
		}

		return false;

	}

	return false;

}


bool ROBOT::move(int direction) {

	if (direction == FORWARD) {

		robotLeftMotors.write(0);
		robotRightMotors.write(255);

		unsigned long time = 0;
		time = millis();

		while ((millis() - time) < 1000) {

			if (readSensor(FRONT_SENSOR, frontSensorValue)) {
				if (frontSensorValue < 10)  {
					break;
				}
			}

		}

		robotLeftMotors.write(127);
		robotRightMotors.write(127);

		return true;

	}
	else if (direction == BACKWARD) {

		robotLeftMotors.write(255);
		robotRightMotors.write(0);

		delay(1000);

		robotLeftMotors.write(127);
		robotRightMotors.write(127);

		return true;

	}

	return false;
}

bool ROBOT::turn(int direction) {

	if (direction == LEFT) {

		robotLeftMotors.write(255);
		robotRightMotors.write(255);

		delay(leftTurnTime);

		robotLeftMotors.write(127);
		robotRightMotors.write(127);

		return true;

	}
	else if (direction == RIGHT) {

		robotLeftMotors.write(0);
		robotRightMotors.write(0);

		delay(rightTurnTime);

		robotLeftMotors.write(127);
		robotRightMotors.write(127);

		return true;

	}

	return false;
}

bool ROBOT::clear() {
	
	if (programSet) {
		programSize = 0;
		strcpy(programString, "");
		programString[50] = '\0';
	}

	return true;
}

long ROBOT::measureDistance(int sensor) {

	if (sensor == FRONT_SENSOR) {
		if (readSensor(FRONT_SENSOR, frontSensorValue)) {
			return frontSensorValue;
		}
	}

	if (sensor == LEFT_SENSOR) {
		if (readSensor(LEFT_SENSOR, leftSensorValue)) {
			return leftSensorValue;
		}
	}

	if (sensor == RIGHT_SENSOR) {
		if (readSensor(RIGHT_SENSOR, rightSensorValue)) {
			return rightSensorValue;
		}

	}

	return -1;
}


bool ROBOT::program(int direction) {

	if (programSize >= 49) {

		writeLCD("PROGRAM FULL");

		programString[programSize] = '\0';
		programSet = true;

		return false;

	}

	if (direction == SELECT) {
		programString[programSize] = '\0';
		programSet = true;

		return false;
	}

	if (direction == LEFT) {
		programString[programSize] = 'L';
		programSize++;
		return true;
	}

	if (direction == RIGHT) {
		programString[programSize] = 'R';
		programSize++;
		return true;
	}

	if (direction == FORWARD) {
		programString[programSize] = 'F';
		programSize++;
		return true;

	}

	if (direction == BACKWARD) {
		programString[programSize] = 'B';
		programSize++;
		return true;
	}

	return false;
}

bool ROBOT::run() {

	if (programSet) {

		Serial.println(programString);

		for (int i = 0; i <= programSize; i++) {

			if (programString[i] == 'B') {
				move(BACKWARD);
			}

			if (programString[i] == 'F') {
				move(FORWARD);
			}

			if (programString[i] == 'L') {
				turn(LEFT);
			}

			if (programString[i] == 'R') {
				turn(RIGHT);
			}
			if (programString[i] == '\0') {
				break;
			}

		}

		return true;

	}

	return false;
}

bool ROBOT::readButton(int button, bool &buttonState, bool &buttonPrevState, long &debounceTime) {

	int reading = digitalRead(button);

	if (reading != buttonPrevState) {
		debounceTime = millis();
	}

	if ((millis() - debounceTime) > debounceDelay) {
		if (reading != buttonState) {
			buttonState = reading;

			if (buttonState == LOW) {
				return true;
			}
		}
	}

	buttonPrevState = reading;

	return false;

}

bool ROBOT::readSensor(int sensor, long &distance) {

	pinMode(sensor, OUTPUT);
	digitalWrite(sensor, LOW);
	delay(10);
	digitalWrite(sensor, HIGH);
	delay(10);
	pinMode(sensor, INPUT);
	int value = 0;
	value = pulseIn(sensor, HIGH);
	distance = value / 29 / 2;

	if (distance > 0) {
		return true;
	}

	return false;
}

bool ROBOT::writeLCD(char* string) {

	if (string != "") {
		LCD.clear();
		LCD.home();
		LCD.print(string);
	
		return true;

	}
	
	return false;

}

bool ROBOT::setTurnTime(int direction, int time) {

	if (direction == LEFT) {
		leftTurnTime = time;
		return true;
	}
	else if (direction == RIGHT) {
		rightTurnTime = time;
		return true;
	}
	
	return false;
}