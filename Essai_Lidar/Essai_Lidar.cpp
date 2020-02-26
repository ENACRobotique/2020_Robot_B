#include "Arduino.h"
#include "LidarXV11.h"
#include "Essai_Lidar.h"

LidarXV11 lidar;

void setup() {
	Serial.begin(115200);
	Serial1.begin(115200);
}

void loop() {
	if (Serial1.available()) {
		uint8_t b = Serial1.read();
		lidar.update(b);
		if (lidar.is_packet_available()) {
			struct Package_Data packet = lidar.get_packet();
			if (packet.index == 110 / 4 + 0xA0) {
				lidar.display_package(&packet);
			}
		}
	}
}



