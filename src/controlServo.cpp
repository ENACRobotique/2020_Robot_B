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
    int pos = init_angle + angle;
    // 0<pos<180
    if (pos>180){
        pos -= 180;
    }
    else if (pos<0){
        pos += 180;
    }
    servo.write(pos);
    delay(15);
}

void ControlServo::resetPos(){
    servo.write(init_angle);
    delay(15);
}