#ifndef OBSTACLE_H
#define OBSTACLE_H

enum ObstacleType {
    LOW_TREE,   // 슬라이딩 필요
    HIGH_TREE   // 점프 필요
};

class Obstacle
{
private:
    ObstacleType type;
    int nTreePos;
    int prevXPos;  // 이전 X 위치 저장

public:
    Obstacle();
    void Update();
    void DrawTree();
    bool IsOutOfScreen();
    bool CheckCollision(int dinoY, bool isSliding);
};

#endif
