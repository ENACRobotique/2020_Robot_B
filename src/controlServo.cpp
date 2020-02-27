#include "controlServo.h"
#include "Arduino.h"
#include "PWMServo.h"
#include "params.h"

ControlServo::ControlServo(){
}

ControlServo::~ControlServo(){
}

void ControlServo::init(int ServoPIN){
    servo.attach(ServoPIN);
}

void ControlServo::moveServo(int angle){
    servo.write(angle);
    delay(15);
}