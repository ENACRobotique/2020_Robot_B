/*
 * odometry.cpp
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */
#include "posEstimator.h"
#include "Arduino.h"
#include "params.h"
#include "MPU6050.h"
#include "Wire.h"

namespace PosEstimator
{

const int iAx = 0;
const int iAy = 1;
const int iAz = 2;
const int iGx = 3;
const int iGy = 4;
const int iGz = 5;

MPU6050 accelgyro;
volatile int _incr1;
volatile int _incr2;

float pos_x, pos_y, pos_theta;

float speed, omega;

void init()
{

	initialize_mpu6050();
	pinMode(ENCODEUR1_A, INPUT_PULLUP);
	pinMode(ENCODEUR1_B, INPUT_PULLUP);
	attachInterrupt(ENCODEUR1_A, isr1, FALLING);
	//attachInterrupt(ENCODEUR1_A, isr1, RISING);
	_incr1 = 0;

	pinMode(ENCODEUR2_A, INPUT_PULLUP);
	pinMode(ENCODEUR2_B, INPUT_PULLUP);
	attachInterrupt(ENCODEUR2_A, isr2, RISING);
	//attachInterrupt(ENCODEUR2_A, isr2, FALLING);
	_incr2 = 0;

	pos_x = pos_y = pos_theta = speed = omega = 0;
}

void isr1()
{
	if (digitalRead(ENCODEUR1_B))
	{
		_incr1++;
		//_incr1--;
	}
	else
	{
		_incr1--;
		//_incr1++;
	}
}

void isr2()
{
	if (digitalRead(ENCODEUR2_B))
	{
		_incr2++;
		//_incr2--;
	}
	else
	{
		_incr2--;
		//_incr2++;
	}
}

float get_pos_x()
{
	return pos_x;
}

float get_pos_y()
{
	return pos_y;
}

float get_pos_theta()
{
	return normalizeAngle(pos_theta);
}

float normalizeAngle(float angle)
{
	float newAngle = angle;
	while (newAngle <= -PI)
		newAngle += TWO_PI;
	while (newAngle > PI)
		newAngle -= TWO_PI;
	return newAngle;
}

float get_speed()
{
	return speed;
}

float get_omega()
{
	return omega;
}

void set_pos(float x, float y, float theta)
{
	pos_x = x;
	pos_y = y;
	pos_theta = PI * theta / 180;
}

void update()
{
	cli();
	int incr1 = _incr1;
	int incr2 = _incr2;
	_incr1 = _incr2 = 0;
	sei();

	float length = ((float)(incr1 + incr2) / 2.0) * INCR_TO_MM;
	float angle = ((float)(incr2 - incr1) * INCR_TO_MM) / WHEELBASE;

	//TODO : vérifier formule
	/*Serial.print(" update() >> postheta=");
		Serial.print(pos_theta);
		Serial.print(" angle=");
		Serial.print(angle);*/
	pos_x = pos_x + length * cos(pos_theta + angle / 2.0);
	pos_y = pos_y + length * sin(pos_theta + angle / 2.0);
	pos_theta = pos_theta + angle; /*
		Serial.print(" pos_x=");
		Serial.print(pos_x);
		Serial.print(" pos_y=");
		Serial.print(pos_y);
		Serial.print(" new pos_theta=");
		Serial.print(pos_theta);
		Serial.println(".");*/
	speed = length / CONTROL_PERIOD;
	omega = angle / CONTROL_PERIOD;

	Serial.print(pos_x);
	Serial.print("\t");
	Serial.print(pos_y);
	Serial.print("\t");
	Serial.println(pos_theta);
	//Serial.print("\t");
	// Serial.print(speed);
	// Serial.print("\t");

	// Serial.println(omega);

	// Serial.print(incr1);
	// Serial.print("\t");
	// Serial.println(incr2);
}

void initialize_mpu6050()
{
// join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
#endif

	// initialize device
	Serial.println("Initializing I2C devices...");
	accelgyro.initialize();

	// verify connection
	Serial.println("Testing device connections...");
	Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

	if (accelgyro.testConnection())
	{
		Serial.println("PID tuning Each Dot = 100 readings");
		/*A tidbit on how PID (PI actually) tuning works. 
    When we change the offset in the MPU6050 we can get instant results. This allows us to use Proportional and 
    integral of the PID to discover the ideal offsets. Integral is the key to discovering these offsets, Integral 
    uses the error from set-point (set-point is zero), it takes a fraction of this error (error * ki) and adds it 
    to the integral value. Each reading narrows the error down to the desired offset. The greater the error from 
    set-point, the more we adjust the integral value. The proportional does its part by hiding the noise from the 
    integral math. The Derivative is not used because of the noise and because the sensor is stationary. With the 
    noise removed the integral value lands on a solid offset after just 600 readings. At the end of each set of 100 
    readings, the integral value is used for the actual offsets and the last proportional reading is ignored due to 
    the fact it reacts to any noise.
  */
		accelgyro.CalibrateAccel(6);
		accelgyro.CalibrateGyro(6);
		Serial.println("\nat 600 Readings");
		accelgyro.PrintActiveOffsets();
		Serial.println();
		accelgyro.CalibrateAccel(1);
		accelgyro.CalibrateGyro(1);
		Serial.println("700 Total Readings");
		accelgyro.PrintActiveOffsets();
		Serial.println();
		accelgyro.CalibrateAccel(1);
		accelgyro.CalibrateGyro(1);
		Serial.println("800 Total Readings");
		accelgyro.PrintActiveOffsets();
		Serial.println();
		accelgyro.CalibrateAccel(1);
		accelgyro.CalibrateGyro(1);
		Serial.println("900 Total Readings");
		accelgyro.PrintActiveOffsets();
		Serial.println();
		accelgyro.CalibrateAccel(1);
		accelgyro.CalibrateGyro(1);
		Serial.println("1000 Total Readings");
		accelgyro.PrintActiveOffsets();
		//Serial.println("\n\n Any of the above offsets will work nice \n\n Lets proof the PID tuning using another method:");
	}
}

} // namespace PosEstimator
