#include <LiquidCrystal.h>
#include <ROBOT.h>
#include <Servo.h>

ROBOT robot;

void setup()
{

	robot.initialise();

	Serial.begin(9600);

	robot.setTurnTime(LEFT, 900);
	robot.setTurnTime(RIGHT, 900);

}

void loop()
{
	
	if (robot.buttonPressed(PROGRAM)) {
		Serial.print("PROGRAM");

		robot.writeLCD("PROGRAM");

		robot.clear();

		while (true) {

			if (robot.buttonPressed(SELECT)) {
				Serial.print("SELECT");

				robot.writeLCD("SELECT");

				robot.program(SELECT);

				break;
			}

			if (robot.buttonPressed(LEFT)) {
				Serial.print("LEFT");

				robot.writeLCD("LEFT");

				robot.program(LEFT);
			}

			if (robot.buttonPressed(RIGHT)) {
				Serial.print("RIGHT");

				robot.writeLCD("RIGHT");

				robot.program(RIGHT);
			}

			if (robot.buttonPressed(FORWARD)) {
				Serial.print("FORWARD");

				robot.writeLCD("FORWARD");

				robot.program(FORWARD);
			}

			if (robot.buttonPressed(BACKWARD)) {
				Serial.print("BACKWARD");

				robot.writeLCD("BACKWARD");

				robot.program(BACKWARD);
			}

		}

	}


	if (robot.buttonPressed(SELECT)) {
		Serial.print("RUN");

		robot.writeLCD("RUN");

		robot.run();
	}


}
