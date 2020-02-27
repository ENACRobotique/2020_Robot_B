#include "MyLidarManager.h"
#include "LidarXV11.h"
#include "Arduino.h"
#include "map.h"
#include "params.h"
#include "posEstimator.h"

MyLidarManager::MyLidarManager() {
}

MyLidarManager::~MyLidarManager() {
}

void MyLidarManager::init(){
}

void MyLidarManager::update(){
    if (Serial1.available()<1) return;
    uint8_t b = Serial1.read();
    lidar.update(b);
}

int MyLidarManager::xObstacle(int lidarAngle){
	int d =  lidar.get_distance(lidarAngle);
	int robotAngle = PosEstimator::get_pos_theta();
	int x = PosEstimator::get_pos_x();
	int xOb =  x + d * cos(lidarAngle * DEG_TO_RAD + robotAngle);
	return(xOb);
}

int MyLidarManager::yObstacle(int lidarAngle){
	int d =  lidar.get_distance(lidarAngle);
	int robotAngle = PosEstimator::get_pos_theta();
	int y = PosEstimator::get_pos_y();
	int yOb =  y + d * sin(lidarAngle * DEG_TO_RAD + robotAngle);
	return(yOb);
}

bool MyLidarManager::is_ignored(int lidarAngle){
	int x = MyLidarManager::xObstacle(lidarAngle);
	int y = MyLidarManager::yObstacle(lidarAngle);
	bool ignored = false;
	if (x < 0 or x >= Map::table_size_x or y < 0 or y >= Map::table_size_y){
		ignored = true;
	}
	else if ((Map::obstacle_map[(int)(y * Map::map_pos_y / Map::table_size_y)][(int)(x * Map::map_pos_x / Map::table_size_x)]) & (0b1 << (7 - (int)(x / Map::PAS) % 8)) ){ // comparaison de carte
		ignored = true;
	}
	return(ignored);
}

bool MyLidarManager::is_ignored2(int x, int y){
	bool ignored = false;
	if (x < 0 or x >= Map::table_size_x or y < 0 or y >= Map::table_size_y){
		ignored = true;
	}
	else if ((Map::obstacle_map[(int)(y * Map::map_pos_y / Map::table_size_y)][(int)(x * Map::map_pos_x / Map::table_size_x)]) & (0b1 << (7 - (int)(x / Map::PAS) % 8)) ){ // comparaison de carte
		ignored = true;
	}
	return(ignored);
}

bool MyLidarManager::obstacleDetected(int lidarAngleA, int lidarAngleB){
	bool obstacle = false;
	int i = 0;
	for(int angle = lidarAngleA; angle <= lidarAngleB; angle++){
		if(lidar.is_valid(angle) and lidar.get_distance(angle) < DIST_MIN){
			i++;
		}
	}
	if(i >= NB_OBSTACLES){
		obstacle = true;
	}

	return(obstacle);
}