/*
 * motorControl.cpp
 *
 *  Created on: 20 mars 2018
 *      Author: elie
 */

#include "posEstimator.h"
#include "Arduino.h"
#include "params.h"
#include "motorControl.h"

int clamp(int inf, int sup, float x)
{
	return min(sup, max(inf, x));
}

int direction_sign(int nb)
{
	if (nb > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

namespace MotorControl
{

float cons_speed;
float cons_omega;
float Ki_speed = 0.3; //0.175; //0.2;
float Kp_speed = 0.5; //0.5;
float Kd_speed = 0;
float Ki_omega = 5;  //3  //15;//20;
float Kp_omega = 20; //90
float Kd_omega = 0;

float error_integrale_speed;
float error_integrale_omega;

float delta_speed;
float delta_omega;
float prev_speed_error;
float prev_omega_error;

void set_cons(float speed, float omega)
{
	cons_speed = speed;
	cons_omega = omega;
}

float get_cons_speed()
{
	return cons_speed;
}

float get_cons_omega()
{
	return cons_omega;
}

void init()
{
	pinMode(MOT1_DIR, OUTPUT);
	pinMode(MOT1_PWM, OUTPUT);
	pinMode(MOT2_DIR, OUTPUT);
	pinMode(MOT2_PWM, OUTPUT);
	cons_omega = cons_speed = 0;
	error_integrale_omega = error_integrale_speed = 0;
	prev_omega_error = prev_speed_error = 0;
}

void update()
{

	float error_speed = cons_speed - PosEstimator::get_speed();
	error_integrale_speed += error_speed;
	delta_speed = error_speed - prev_speed_error;
	prev_speed_error = error_integrale_speed;
	float cmd_speed = Kp_speed * error_speed + Ki_speed * error_integrale_speed + Kd_speed * delta_speed;

	float error_omega = cons_omega - PosEstimator::get_omega();
	error_integrale_omega += error_omega;
	delta_omega = error_omega - prev_omega_error;
	prev_omega_error = error_omega;
	float cmd_omega = Kp_omega * error_omega + Ki_omega * error_integrale_omega + Kd_omega * delta_omega;

	int cmd_mot1 = clamp(-255, 255, cmd_speed + cmd_omega);
	int cmd_mot2 = clamp(-255, 255, cmd_speed - cmd_omega);

	analogWrite(MOT1_PWM, abs(cmd_mot1));
	digitalWrite(MOT1_DIR, direction_sign(cmd_mot1));
	analogWrite(MOT2_PWM, abs(cmd_mot2));
	digitalWrite(MOT2_DIR, direction_sign(cmd_mot2));

	// Serial.print(cons_speed);
	// Serial.print("\t");
	// Serial.print(PosEstimator::get_speed());
	// Serial.print("\t");
	// Serial.print(cmd_mot1);
	// Serial.print("\t");
	// Serial.print(cmd_mot2);
	// Serial.print("\t");
	// Serial.println();
	// Serial.print(cons_omega);
	// Serial.print("\t");
	// Serial.println(PosEstimator::get_omega());
	// Serial.print("\t");
	// Serial.println();
	// Serial.print(error_speed);
	// Serial.println("\t");
	// Serial.print(error_omega);
	// Serial.println("\t");
}
} // namespace MotorControl