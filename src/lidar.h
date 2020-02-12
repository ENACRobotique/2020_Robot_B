/*
 * lidar.h
 *
 *  Created on: 8 mai 2019
 *      Author: robot
 */

#ifndef LIDAR_H_
#define LIDAR_H_

class Lidar{
public:
	Lidar();
	void set_pin_in(int pin1, int pin2, int pin3, int pin4, int pin5);
	int get_zone1();
	int get_zone2();
	int get_zone3();

	void comm_up();
	bool comm_down();
private:

	int zone1;
	int zone2;
	int zone3;

	int pin_in1;
	int pin_in2;
	int pin_in3;
	int pin_in4;
	int pin_in5;
};

#endif /* LIDAR_H_ */
