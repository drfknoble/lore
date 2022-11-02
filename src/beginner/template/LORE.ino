/*
 *	Low-cost Open-source Robotics Educational (LORE) kits are provided "as is" with no warranties whatsoever,
 *	including any warranty of merchantability, non - infringement, fitness for any particular purpose,
 *	or any warranty otherwise arising out of any proposal, specification or sample.
 * 	LORE kits(and manufacturers and distributors) disclaims all liability, including liability for infringement of any proprietary rights,
 *	relating to use of information in any documents and files and software and no license, express or implied, by LORE kits or otherwise,
 *	to any intellectual property rights is granted herein.LORE kits(and manufacturers and distributors) assumes no responsibility or liability
 *	for any errors or inaccuracies that may appear in any documentation or files or any software that may be provided.
 *	The information in any documents or files is furnished for informational use only, is subject to change without notice,
 *	and should not be construed as a commitment by LORE kits(and manufacturers and distributors).
 *
 *	Filename: Lore.ino.
 *	Description: Lore.ino is the default program running on the LORE kit's Arduino Uno REV. 3.
 *	Version: 1.0.
 *	Edited: N/A.
 */

/*
 *	Headers. Header files are declared here. The #include keyword is used to include a .h header file.
 */

#include <Servo.h>
#include <LiquidCrystal.h>

/*
 *	Defines. Defines are declared here. Defines aren't variables; rather they're statements which replace key words with values when
 *	the program is compiled.
 */

#define BACKWARD 7
#define FORWARD 8
#define RIGHT 9
#define LEFT 10
#define SELECT 11
#define PROGRAM 12

#define RS A0
#define E A1
#define D4 A2
#define D5 A3
#define D6 A4
#define D7 A5

#define FRONT_SENSOR 2
#define LEFT_SENSOR 3
#define RIGHT_SENSOR 4

#define LEFT_MOTORS 5
#define RIGHT_MOTORS 6

/*
 *	Global Variables. Global variables are declared here. Format: variableType variableName; or variableType variableName = defaultValue;
 */

long debounceDelay = 50;

long programDebounceTime = 0;
long selectDebounceTime = 0;
long leftDebounceTime = 0;
long rightDebounceTime = 0;
long forwardDebounceTime = 0;
long backwardDebounceTime = 0;

int programState = HIGH;
int programPrevState = HIGH;
int selectState = HIGH;
int selectPrevState = HIGH;
int leftState = HIGH;
int leftPrevState = HIGH;
int rightState = HIGH;
int rightPrevState = HIGH;
int forwardState = HIGH;
int forwardPrevState = HIGH;
int backwardState = HIGH;
int backwardPrevState = HIGH;

long frontSensorValue = 0;
long leftSensorValue = 0;
long rightSensorValue = 0;

char programString[50] = {};
int programSet = 0;
int programSize = 0;

/*
 * Class instances. Class objects are declared here.
 */

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
Servo leftMotors, rightMotors;

/*
 *	Function Declarations. Function prototypes are declared here. Format: returnType functionName(parameterType parameterName, ...);
 *	The function contents are defined after void loop().
 */

bool drive(int direction);
bool readButton(int button, int &buttonState, int &buttonPrevState, long &debounceTime);
bool readSensor(int sensor, long &distance);

/*
*	Function:		void setup().
*	Returns:		None.
*	Parameters:		None.
*	Description:	Setup initialises the program's variables. Here the pinModes of the PROGRAM through to BACKWARD buttons are set as inputs
*					and then internal pull up resistors enables by writing a HIGH logic level to the buttons' associated pins. Sensors are configured
*					as outputs and their states set to the LOW logic level. Servo motors are attached to LEFT_MOTORS and RIGHT_MOTORS pins and set to a neutral
*					position. Lastly, the serial port is opened using a default baud rate of 9600 and 8N1 parameters (8 data-bits, no parity, 1 stop bit).
*/

void setup()
{

	// Initialise the LCD screen. Set size at 16 channels x 2 rows.

	lcd.begin(16, 2);
	lcd.clear();
	lcd.home();

	// Initialise the pushbuttons. Enable internal pull-ups. Logic LOW = button pressed; else HIGH.

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

	// Initialise the sensors. Configure as outputs to start with.

	pinMode(FRONT_SENSOR, OUTPUT);
	digitalWrite(FRONT_SENSOR, LOW);

	pinMode(LEFT_SENSOR, OUTPUT);
	digitalWrite(LEFT_SENSOR, LOW);

	pinMode(RIGHT_SENSOR, OUTPUT);
	digitalWrite(RIGHT_SENSOR, LOW);

	// Initialise servo motors.

	leftMotors.attach(LEFT_MOTORS);
	leftMotors.write(127);

	rightMotors.attach(RIGHT_MOTORS);
	rightMotors.write(127);

	// Initialise the serial port. Default buad rate 9600, 8 Data Bits, No Parity, 1 Stop Bit (8N1).

	Serial.begin(9600);

}

/*
 *	Function:		void loop().
 *	Returns:		None.
 *	Parameters:		None.
 *	Description:	Loops continuously, executing program logic. Here, loop() checks to see if the program button is pressed. If 
 *					it is, the program enters "programming mode"; where, each button is used to program the robot in an event- and time-based
 *					method. When the program is full, or the user presses the SELECT button, the program breaks out of programming mode. Loop() then
 *					waits for the SELECT button to be pressed again; at which point, the program is executed.
 */

void loop()
{


	if (readButton(PROGRAM, programState, programPrevState, programDebounceTime)) {

		lcd.clear();
		lcd.home();
		lcd.print("PROGRAM");

		programSize = 0;
		strcpy(programString, "");
		programString[50] = '\0';

		while (true) {

			if (readButton(SELECT, selectState, selectPrevState, selectDebounceTime)) {

				lcd.clear();
				lcd.home();
				lcd.print("SELECT");

				programString[programSize] = '\0';

				programSet = true;

				break;

			}

			if (readButton(LEFT, leftState, leftPrevState, leftDebounceTime)) {

				lcd.clear();
				lcd.home();
				lcd.print("LEFT");

				programString[programSize] = 'L';
				programSize++;

			}

			if (readButton(RIGHT, rightState, rightPrevState, rightDebounceTime)) {

				lcd.clear();
				lcd.home();
				lcd.print("RIGHT");

				programString[programSize] = 'R';
				programSize++;

			}

			if (readButton(FORWARD, forwardState, forwardPrevState, forwardDebounceTime)) {

				lcd.clear();
				lcd.home();
				lcd.print("FORWARD");

				programString[programSize] = 'F';
				programSize++;

			}

			if (readButton(BACKWARD, backwardState, backwardPrevState, backwardDebounceTime)) {

				lcd.clear();
				lcd.home();
				lcd.print("BACKWARD");

				programString[programSize] = 'B';
				programSize++;

			}

			if (programSize >= 49) {


				lcd.clear();
				lcd.home();
				lcd.print("PROGRAM FULL");

				programString[programSize] = '\0';

				programSet = true;

				break;

			}

		}

	}

	if (readButton(SELECT, selectState, selectPrevState, selectDebounceTime)) {

		if (programSet) {

			Serial.println(programString);
			
			for (int i = 0; i <= programSize; i++) {

				if (programString[i] == 'B') {
					drive(BACKWARD);
				}
				
				if (programString[i] == 'F') {
					drive(FORWARD);
				}
				
				if (programString[i] == 'L') {
					drive(LEFT);
				}
				
				if (programString[i] == 'R') {
					drive(RIGHT);
				} 
				if (programString[i] == '\0') {
					break;
				}

			}

		}

	}

	
}

/*
 *	Function:		bool drive(int direction).
 *	Returns:		bool.
 *	Parameters:		int direction.
 *	Description:	Reads in the direction the robot needs to move in. If direction is FORWARD, read front sensor and drive for 1000 ms. If sensorValue is less
 *					than a threshold, stop and move onto next instruction. If direction is !FORWARD, move for 1000 ms.
 */

bool drive(int direction) {

	if (direction == FORWARD) {

		leftMotors.write(0);
		rightMotors.write(255);

		unsigned long time = 0;
		time = millis();

		while ((millis() - time) < 1000) {
			
			readSensor(FRONT_SENSOR, frontSensorValue);

			if (frontSensorValue < 5) {
				break;
			}

		}
			
		leftMotors.write(127);
		rightMotors.write(127);

		return true;

	}
	else if (direction == BACKWARD) {

		leftMotors.write(255);
		rightMotors.write(0);

		delay(1000);

		leftMotors.write(127);
		rightMotors.write(127);

		return true;

	}
	else if (direction == LEFT) {

		leftMotors.write(255);
		rightMotors.write(255);

		delay(900);

		leftMotors.write(127);
		rightMotors.write(127);

		return true;

	}
	else if (direction == RIGHT) {

		leftMotors.write(0);
		rightMotors.write(0);

		delay(900);

		leftMotors.write(127);
		rightMotors.write(127);

		return true;

	}

	return false;
}


/*
*	Function:		bool readButton(int button, int &buttonState, int &buttonPrevState, long &debounceTime).
*	Returns:		bool.
*	Parameters:		int button, int &buttonState, int &buttonPrevState, long &debounceTime.
*	Description:	
*/

bool readButton(int button, int &buttonState, int &buttonPrevState, long &debounceTime) {

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

/*
*	Function:		bool readSensor(int sensor, long &distance).
*	Returns:		bool.
*	Parameters:		int sensor, long &distance.
*	Description:
*/

bool readSensor(int sensor, long &distance) {

	pinMode(sensor, OUTPUT);
	digitalWrite(sensor, LOW);
	delay(10);
	digitalWrite(sensor, HIGH);
	delay(10);
	pinMode(sensor, INPUT);
	int value = 0;
	value = pulseIn(sensor, HIGH);
	distance = value / 29 / 2;

	if (distance != 0) {
		return true;
	}

	return false;
}
