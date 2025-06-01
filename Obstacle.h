#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "BoundingBox.h"

enum ObstacleType {
    LOW, // 슬라이딩 필요
    HIGH, // 점프 필요
    TWO_HIGH // 2단 점프
};

// 장애물 생성, 이동, 충돌 담당
class Obstacle
{
private:
    ObstacleType type;
    int x, y; // x,y 축 위치
    int width, height; // 너비, 높이
    int prevX; // 이전 X 위치 저장
public:
    Obstacle();
    void Update(); // 위치 이동
    void DrawObstacle(); // 콘솔에 출력
    bool IsOutOfScreen(); // 화면에서 벗어났는지 확인
    BoundingBox GetBoundingBox() const; // 충돌 박스
};
#endif