/*
 * LidarXV11.cpp
 *
 *  Created on: 18 avr. 2019
 *      Author: robot
 */

#include "LidarXV11.h"

LidarXV11::LidarXV11() : speed(0){
	state = WAIT_START;
	packet = {0};
	packet_available = false;
	tmp = 0;
	c = 0;
	tmpck = 0;
	ck = 0;
	chk32 = 0;
	checksum = 0;
}

LidarXV11::~LidarXV11() {
}

void LidarXV11::update(uint8_t byte) {
	uint16_t checksum_rx;
	//Serial1.write(byte);
	switch (state) {
	case WAIT_START:
		if (byte == 0xFA){
			state = WAIT_INDEX;
			ck = 0;
			chk32 = 0;
		}
		break;
	case WAIT_INDEX:
		if (byte <= 0xF9 && byte >= 0xA0) {
			packet.index = (int)byte;
			packet_available = false;
			state = WAIT_SPEED_L;
		}
		else{
			state = WAIT_START;
		}
		break;
	case WAIT_SPEED_L:
		tmp = byte;
		state = WAIT_SPEED_H;
		break;
	case WAIT_SPEED_H:
		packet.speed = ((byte << 8) | tmp) / 64;
		c = 0;
		state = READ_DATA_0;
		break;
	case READ_DATA_0:
		if (c < 4){
			data[c] = byte;
			c++;
		}
		if (c == 4){
			read_data(0);
			c = 0;
			state = READ_DATA_1;
		}
		break;
	case READ_DATA_1:
		if (c < 4){
			data[c] = byte;
			c++;
		}
		if (c == 4){
			read_data(1);
			c = 0;
			state = READ_DATA_2;
		}

		break;
	case READ_DATA_2:
		if (c < 4){
			data[c] = byte;
			c++;
		}
		if (c == 4){
			read_data(2);
			c = 0;
			state = READ_DATA_3;
		}
		break;
	case READ_DATA_3:
		if (c < 4){
			data[c] = byte;
			c++;
		}
		if (c == 4){
			read_data(3);
			c = 0;
			state = WAIT_CHECKSUM_L;
		}
		break;
	case WAIT_CHECKSUM_L:
		checksum = (chk32 & 0x7FFF) + (chk32 >> 15);
		checksum = checksum & 0x7FFF;

		tmp = byte;
		state = WAIT_CHECKSUM_H;
		break;
	case WAIT_CHECKSUM_H:
		checksum_rx = (byte << 8) | tmp;
		if (checksum == checksum_rx){
			packet_available = true;
			speed = packet.speed;
		}
		else{
			//Serial1.println("LIDAR CHECKSUM INVALID");
		}
		state = WAIT_START;
		break;
	default:
		Serial.println("No state");
		break;
	}
	if (ck % 2 == 0){
		tmpck = byte;
	}
	else{
		uint16_t d = tmpck + (byte << 8);
		chk32 = (chk32 << 1) + d;
	}
	ck++;
}

void LidarXV11::display_package(struct Package_Data* p) {
	Serial.print(p->index - 0xA0);
	Serial.print("   ");
	Serial.print(p->speed);
	Serial.print(" | ");
	for (int i = 0; i < 4; i++ ){
		Serial.print((p->index - 0xA0)  * 4 + i);
		Serial.print("    ");
		Serial.print(p->distance[i]);
		Serial.print("   ");
		Serial.print(p->invalid[i]);
		Serial.print("   ");
		Serial.print(p->warning[i]);
		Serial.print("   ");
		Serial.print(p->strength[i]);
		Serial.print(" | ");
	}
	Serial.println();
}

void LidarXV11::read_data(int i) {
	packet.distance[i] = ((0b00111111 & data[1]) << 8) | data[0];
	packet.invalid[i] = (data[1] & 0b10000000);
	packet.warning[i] = (data[1] & 0b01000000);
	packet.strength[i] = (data[3] << 8) | data[2];
	distance_angle[(packet.index - 0xA0)  * 4 + i] = packet.distance[i];
	valid_angle[(packet.index - 0xA0)  * 4 + i] = !packet.invalid[i];
	//Serial.println(valid_angle[(packet.index - 0xA0)  * 4 + i]);

}

int LidarXV11::get_distance(int angle){
	return distance_angle[angle];
}

bool LidarXV11::is_valid(int angle){
	return valid_angle[angle];
}


void LidarXV11::init() {
	//serial = lidar_serial;
	//serial.begin(115200);
	//Serial4.begin(115200);
}
