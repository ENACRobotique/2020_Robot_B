#include "Arduino.h"
#include "params.h"



void init()
{
    pinMode(SONO_TRIGGER, OUTPUT);
    digitalWrite(SONO_TRIGGER, LOW);
    pinMode(SONO_ECHO, INPUT);

}

// Return la distance mesuree en metre
float mesure()
{
    digitalWrite(SONO_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONO_TRIGGER, LOW);

    long mesure = pulseIn(SONO_ECHO, HIGH, MEASURE_TIMEOUT);
    double distance_m = mesure*SOUND_SPEED/(2*CONVERT);
    return distance_m;
}