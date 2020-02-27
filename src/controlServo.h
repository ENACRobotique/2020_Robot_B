#ifndef CONTROLSERVO_H_
#define CONTROLSERVO_H_

#include "Arduino.h"
#include "PWMServo.h"


class ControlServo{    
public:
    ControlServo();
    virtual ~ControlServo();
    void init(int ServoPIN);
    void moveServo(int angle);
    PWMServo servo;
};

#endif