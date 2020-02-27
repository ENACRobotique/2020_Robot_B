#ifndef CONTROLSERVO_H_
#define CONTROLSERVO_H_

#include "Arduino.h"
#include "PWMServo.h"


class ControlServo{    
public:
    ControlServo();
    virtual ~ControlServo();
    void init(int ServoPIN);
    void moveServo(int angle); //input a delta angle
    void resetPos();
    PWMServo servo;
private:
    int init_angle = servo.read();
};

#endif