#ifndef OBSTACLE_H
#define OBSTACLE_H

enum ObstacleType {
    LOW_TREE,   // 슬라이딩 필요
    HIGH_TREE   // 점프 필요
};

// 장애물 생성, 이동, 충돌 담당
class Obstacle
{
private:
    ObstacleType type;
    int nTreePos; // 현재 x 좌표 
    int prevXPos; // 이전 X 위치 저장

public:
    Obstacle();
    void Update(); // 위치 이동
    void DrawTree(); // 콘솔에 출력
    bool IsOutOfScreen(); // 화면에서 벗어났는지 확인
    bool CheckCollision(int dinoY, bool isSliding); // 충돌 판정
};
#endif