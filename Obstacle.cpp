#include "Obstacle.h"
#include "Console.h"
#include <iostream>
#include <cstdlib> 

constexpr int Y_BASE = 20; // 장애물 기준 y좌표
constexpr int TREE_START = 100; // 장애물 시작 x좌표
constexpr int TREE_END = 0; // 나무가 사라질 x좌표

Obstacle::Obstacle() : x(TREE_START), y(Y_BASE), prevX(TREE_START), height(0), width(0) {
    type = static_cast<ObstacleType>(rand() % 3); // 랜덤하게 장애물 선택
}

// 나무 위치
void Obstacle::Update()
{
    prevX = x;
    if (x > TREE_END)
        x -= 2; // 왼쪽으로 이동
    else{
        x = TREE_START;  // 오른쪽 끝에서 생성
        type = (rand() % 2 == 0) ? LOW : HIGH;
    }

    if (type == LOW){ // 슬라이딩 장애물 출력 시작 y값
        width = 3;
        height = 3;
        y = Y_BASE - 2;
    }
    else if(type == HIGH){
        width = 2;
        height = 2;
        y = Y_BASE + 3;
    }
    else{
        width = 6;
        height = 2;
        y = Y_BASE + 1;
    }
}

// 나무 그리기
void Obstacle::DrawTree()
{
    // 이전 위치 지우기
    if (prevX >= 0) {
        for (int i = 0; i < 3; i++){
            Console::SetKeyCursor(prevX, y + i); std::cout << "       ";
        }
    }

    int checkX = x;
    // 장애물 출력
    for (int i = 0; i < height; i++) {
        Console::SetKeyCursor(checkX, y + i);
        for (int j = 0; j < width; j ++){
            std::cout << "o";
        }
        std::cout << "\n";
    }
    
}

// 화면에서 사라질 위치
bool Obstacle::IsOutOfScreen() { 
    return x <= TREE_END;
}

// 충돌 박스 리턴
BoundingBox Obstacle::GetBoundingBox() const {
    return {x, y, width, height}; // 장애물 위치 및 크기
}