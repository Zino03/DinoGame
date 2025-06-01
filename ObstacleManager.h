#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H
#include <vector>
#include "Obstacle.h"

class GameManager {
private:
    std::vector<Obstacle> obstacles;
    int frameCount = 0;            // 프레임 수 (생성 간격 제어용)
    int spawnInterval = 50;        // 기본 생성 간격 (프레임 수 기준)
    int minObstacleDistance = 20;  // 장애물 간 최소 거리
    int stage = 1;

public:
    void UpdateObstacles();
    void DrawObstacles();
    void IncreaseStage(); // 난이도 상승
};
#endif