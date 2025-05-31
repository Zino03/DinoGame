#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "BoundingBox.h"

enum ObstacleType {
    LOW_TREE,   // 슬라이딩 필요
    HIGH_TREE   // 점프 필요
};

// 장애물 생성, 이동, 충돌 담당
class Obstacle
{
private:
    ObstacleType type;
    int x, y; // 좌표
    int width, height; // 크기
    int prevX; // 이전 X 위치 저장
public:
    Obstacle();
    void Update(); // 위치 이동
    void DrawTree(); // 콘솔에 출력
    bool IsOutOfScreen(); // 화면에서 벗어났는지 확인
    BoundingBox GetBoundingBox() const; // 충돌 박스
};
#endif