#include "Secondary2019Code.h"
#include "Metro.h"
#include "params.h"
#include "posEstimator.h"
#include "motorControl.h"
#include "Navigator.h"
#include "Servo.h"
//#include "lidar/LidarXV11.h"
//#include "lidar/LidarManager.h"

#include "MPU6050.h"

Metro controlTime = Metro((unsigned long)(CONTROL_PERIOD * 1000));
Metro navigatorTime = Metro(NAVIGATOR_TIME_PERIOD * 1000);
Metro debugLed = Metro(500);
Metro testAsserv = Metro(500);

int PIN_LED = 13;
uint32_t deb;

//The setup function is called once at startup of the sketch
void setup()
{

	delay(1000);
	pinMode(PIN_LED, OUTPUT);
	pinMode(MOT_LIDAR, OUTPUT);
	digitalWrite(PIN_LED,HIGH);

	pinMode(COLOR, INPUT_PULLUP);
	pinMode(BATT_CHARGE, INPUT);

	Serial1.begin(115200);
	Serial2.begin(115200);
	Serial.begin(115200);
	Serial.print("Init");
	// while (!Serial)
	{
	}
	Serial.println("INIT Serial");
	Serial.println(BATT_CHARGE);
	PosEstimator::init();
	MotorControl::init();
	controlTime.reset();
	navigatorTime.reset();
	deb = millis();
	//navigator.move_to(2600,0);
	PosEstimator::set_pos(0, 0, 0);

	//MotorControl::set_cons(100,0);

	
}

int i = 0;
int j = 0;
bool move_asked = false;

// The loop function is called in an endless loop
void loop()
{
	
	if (controlTime.check())
	{
		Serial.println(Serial2.readString());
		PosEstimator ::update();
		MotorControl::update();
	}
	// if(testAsserv.check()){

	// 		if(millis()-deb > 60000){
	// 			navigator.turn_to(PosEstimator::get_pos_theta()*RAD_TO_DEG);
	// 		}
	// 		else{
	// 			float angleConsigne = PosEstimator::get_pos_theta()*RAD_TO_DEG + 120;
	// 			navigator.turn_to(angleConsigne);
	// 		}
	// }
	if (testAsserv.check())
	{
		if (j == 0 && !move_asked)
		{
			navigator.move_to(400, 0);
			move_asked = true;
		}
		else if (j == 1 && !move_asked)
		{
			navigator.move_to(400, 400);
			move_asked = true;
		}
		else if (j == 2 && !move_asked)
		{
			navigator.move_to(0, 400);
			move_asked = true;
		}
		else if (j == 3 && !move_asked)
		{
			navigator.move_to(0, 0);
			move_asked = true;
		}

		if (navigator.isTrajectoryFinished())
		{
			j = (j + 1) % 4;
			move_asked = false;
		}
	}

	if (navigatorTime.check())
	{
		navigator.update();
	}
}
