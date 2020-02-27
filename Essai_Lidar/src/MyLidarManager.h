#include "LidarXV11.h"
#include "Arduino.h"

class MyLidarManager {
public:
    MyLidarManager();
    virtual ~MyLidarManager();
    void init();
    void update();
    int xObstacle(int lidarAngle);
    int yObstacle(int lidarAngle);
    bool is_ignored(int lidarAngle);
    bool is_ignored2(int x, int y);
    bool obstacleDetected(int lidarAngleA, int lidarAngleB);

    LidarXV11 lidar = LidarXV11();

private:
    const int NB_OBSTACLES = 2;
	const int DIST_MIN = 350;
};