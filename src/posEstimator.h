/*
 * odometry.h
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */

#ifndef posEstimator_H_
#define posEstimator_H_

namespace PosEstimator
{
void isr1();
void isr2();

void initialize_mpu6050();

void update();
void init();

void set_pos(float x, float y, float theta);

float get_pos_x();
float get_pos_y();
float get_pos_theta();
float normalizeAngle(float angle);
float get_speed();
float get_omega();
} // namespace PosEstimator

#endif /* ODOMETRY_H_ */
