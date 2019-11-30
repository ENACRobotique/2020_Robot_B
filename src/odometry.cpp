/*
 * odometry.cpp
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */
#include "odometry.h"
#include "Arduino.h"
#include "params.h"

namespace Odometry{

	volatile int _incr1;
	volatile int _incr2;

	float pos_x, pos_y, pos_theta;

	float speed, omega;

	void init(){
		pinMode(ENCODEUR1_A,INPUT_PULLUP);
		pinMode(ENCODEUR1_B,INPUT_PULLUP);
		attachInterrupt(ENCODEUR1_A, isr1, FALLING);
		//attachInterrupt(ENCODEUR1_A, isr1, RISING);
		_incr1 = 0;

		pinMode(ENCODEUR2_A,INPUT_PULLUP);
		pinMode(ENCODEUR2_B,INPUT_PULLUP);
		attachInterrupt(ENCODEUR2_A, isr2, RISING);
		//attachInterrupt(ENCODEUR2_A, isr2, FALLING);
		_incr2 = 0;

		pos_x = pos_y = pos_theta = speed = omega = 0;

	}

	void isr1() {
		if(digitalRead(ENCODEUR1_B)) {
			_incr1++;
			//_incr1--;
		}
		else {
			_incr1--;
			//_incr1++;
		}
	}

	void isr2() {
			if(digitalRead(ENCODEUR2_B)) {
				_incr2++;
				//_incr2--;
			}
			else {
				_incr2--;
				//_incr2++;
			}
		}


	float get_pos_x(){
		return pos_x;
	}

	float get_pos_y(){
		return pos_y;
	}

	float get_pos_theta(){
		return normalizeAngle(pos_theta);
	}


	float normalizeAngle(float angle)
	{
	    float newAngle = angle;
	    while (newAngle <= -PI) newAngle += TWO_PI;
	    while (newAngle > PI) newAngle -= TWO_PI;
	    return newAngle;
	}

	float get_speed(){
		return speed;
	}

	float get_omega(){
		return omega;
	}

	void set_pos(float x, float y, float theta){
		pos_x = x;
		pos_y = y;
		pos_theta = PI*theta/180;
	}

	void update() {
		cli();
		int incr1 = _incr1;
		int incr2 = _incr2;
		_incr1 = _incr2 = 0;
		sei();

		float length = ((float)(incr1+incr2)/2.0)*INCR_TO_MM;
		float angle = ((float)(incr2-incr1)*INCR_TO_MM)/WHEELBASE;

		//TODO : vérifier formule
		/*Serial.print(" update() >> postheta=");
		Serial.print(pos_theta);
		Serial.print(" angle=");
		Serial.print(angle);*/
		pos_x = pos_x + length*cos(pos_theta + angle/2.0);
		pos_y = pos_y + length*sin(pos_theta + angle/2.0);
		pos_theta = pos_theta + angle;/*
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
}






