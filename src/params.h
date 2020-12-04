/*
 * params.h
 *
 *  Created on: 18 mars 2018
 *      Author: elie
 */

#ifndef PARAMS_H_
#define PARAMS_H_
#include "Arduino.h"

const unsigned long TIME_RACE = 100000;

/*
const int lidar_av1 = 80;
const int lidar_av2 = 100;
*/
const int lidar_avred1 = 85;
const int lidar_avred2 = 95;
const int lidar_av1 = 40;
const int lidar_av2 = 140;
const int lidar_ar1 = 220;
const int lidar_ar2 = 320;
const int lidar_arred1 = 265;
const int lidar_arred2 = 275;
const int lidar_turn1 = 0;
const int lidar_turn2 = 359;

const int ENCODEUR1_A = 21;
const int ENCODEUR1_B = 20;
const int ENCODEUR2_A = 17;
const int ENCODEUR2_B = 16;

const int MOT1_PWM = 5;
const int MOT1_DIR = 6;
const int MOT2_PWM = 29;
const int MOT2_DIR = 28;

const int BATT_CHARGE = 37;

const int US_RANGE = 35;
const int US_RANGE_DIMINUSHED = 25;

//Servo Moteur
const int SERVO_BRAS_PRINCIPAL = 39;
const int SERVO_BRAS_SECONDAIRE = 15;
const int SERVO_PINCE_SUPERIEURE = 37;
const int SERVO_PINCE_INFERIEURE;
const int SERVO_MANCHE_AIR;
const int SERVO_FLAG;

const int MOT_GALET_L = 35;
const int MOT_LIDAR = 35;

const int COLOR = 26;
const int TIRETTE = 25;

const int SPARE1 = 10;
const int SPARE2 = 9;
const int SPARE3 = 8;
const int SPARE4 = 7;

const int DYNAMIXEL_CONTROL = 30;
const int DYNAMIXEL_ID =1;

const int EMERGENCY_BRAKE = 1800;
const int ACCEL_MAX = 500;
const int ACCEL_MAX_THROW = 100;
const int SPEED_MAX = 350;

const float ACCEL_OMEGA_MAX = 1;
const float OMEGA_MAX = 1.5;

const float ADMITTED_OMEGA_ERROR = 0.03;
const float ADMITTED_SPEED_ERROR = 10;

const float ADMITTED_POSITION_ERROR = 10;
const float ADMITTED_ANGLE_ERROR = 0.01;

const float MAX_DRIFT = 0.1;

const float WHEEL_DIAMETER = 54.0;
const float WHEELBASE = 230.0;

const float INCR_TO_MM = PI*WHEEL_DIAMETER/805.12;

const float CONTROL_PERIOD = 0.02;
const float NAVIGATOR_TIME_PERIOD = 0.05;

const unsigned long THROW_DURATION = 20000;
const unsigned long SERVO_MOVEMENT_DURATION = 1000;
const unsigned long DETECTION_STOP_TIME = 1500;

const int MANDIBULE_DROITE_BAS = 135;
const int MANDIBULE_GAUCHE_BAS = 150;
const int MANDIBULE_DROITE_HAUT = 0;
const int MANDIBULE_GAUCHE_HAUT = 25;

const int GREEN = 1;
const int ORANGE = !GREEN;
const int PURPLE = 1;
const int YELLOW = !PURPLE;

const int NB_US = 4;
#endif /* PARAMS_H_ */
