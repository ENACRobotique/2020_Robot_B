#include "lidar.h"
#include "params.h"

Lidar::Lidar(){
	zone1=0;
	zone2=0;
	zone3=0;

	pin_in1=1;
	pin_in2=0;
	pin_in3=0;
	pin_in4=0;
	pin_in5=0;
}

int Lidar::get_zone1(){
	return digitalRead(LID_PIN_OUT1);
}

int Lidar::get_zone2(){
	return digitalRead(LID_PIN_OUT2);
}

int Lidar::get_zone3(){
	return digitalRead(LID_PIN_OUT3);
}

void Lidar::set_pin_in(int pin1, int pin2, int pin3, int pin4, int pin5){
	pin_in1 = pin1;
	pin_in2 = pin2;
	pin_in3 = pin3;
	pin_in4 = pin4;
	pin_in5 = pin5;
}

void Lidar::comm_up(){
	digitalWrite(LID_PIN_IN1,pin_in1);
	digitalWrite(LID_PIN_IN2,pin_in2);
	digitalWrite(LID_PIN_IN3,pin_in3);
	digitalWrite(LID_PIN_IN4,pin_in4);
	digitalWrite(LID_PIN_IN5,pin_in5);
}

bool Lidar::comm_down(){
	int old_1 = zone1;
	int old_2 = zone2;
	int old_3 = zone3;
	zone1 = digitalRead(LID_PIN_OUT1);
	zone2 = digitalRead(LID_PIN_OUT2);
	zone3 = digitalRead(LID_PIN_OUT3);
	return (old_1 != zone1 || old_2 != zone2 || old_3 != zone3);
}