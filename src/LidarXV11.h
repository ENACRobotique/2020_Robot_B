/*
 * LidarXV11.h
 *
 *  Created on: 18 avr. 2019
 *      Author: robot
 */
#ifndef LIDARXV11_H_
#define LIDARXV11_H_
#include "Arduino.h"

enum State {
	WAIT_START,
	WAIT_INDEX,
	WAIT_SPEED_L,
	WAIT_SPEED_H,
	READ_DATA_0,
	READ_DATA_1,
	READ_DATA_2,
	READ_DATA_3,
	WAIT_CHECKSUM_L,
	WAIT_CHECKSUM_H
};


struct Package_Data {
	int index;
	int invalid[4];
	int warning[4];
	int distance[4];
	int strength[4];
	float speed;
};

class LidarXV11 {
public:
	LidarXV11();
	virtual ~LidarXV11();

	void init();
	void update(uint8_t byte);
	void display_package(struct Package_Data* p);
	int get_distance(int angle);
	bool is_valid(int angle);
	bool is_packet_available(){
		return(packet_available);
	}
	struct Package_Data get_packet(){
		return(packet);
	}
	float getSpeed(){
		return(speed);
	}

private:
	void read_data(int i);

	enum State state;
	struct Package_Data packet;
	bool packet_available;
	uint16_t tmp;
	uint8_t data[4];
	int c;
	uint8_t tmpck;
	int ck;
	uint32_t chk32;
	uint16_t checksum;
	int distance_angle[360];
	int valid_angle[360];
	float speed;
};

#endif /* LIDARXV11_H_ */
