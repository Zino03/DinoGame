#include "Obstacle.h"
#include "Console.h"
#include <iostream>
#include <cstdlib> 

constexpr int Y_BASE = 20; // 장애물 기준 y좌표
constexpr int OBSTACLE_START = 100; // 장애물 시작 x좌표
constexpr int OBSTACLE_SPAWN = 0; // 장애물이 생성 최소 거리 x좌표
constexpr int OBSTACLE_END = 0; // 장애물이 사라질 x좌표

Obstacle::Obstacle() : x(OBSTACLE_START), y(Y_BASE), prevX(OBSTACLE_START), height(0), width(0) {
    type = static_cast<ObstacleType>(rand() % 3); // 랜덤하게 장애물 선택
}

// 나무 위치
void Obstacle::Update()
{
    prevX = x;
    if (x > OBSTACLE_END)
        x -= 2; // 왼쪽으로 이동
    else{
        x = OBSTACLE_START;  // 오른쪽 끝에서 생성
        type = static_cast<ObstacleType>(rand() % 3);
    }

    if (type == LOW){ // 슬라이딩 장애물 출력 시작 y값
        width = 2;
        height = 5;
        y = Y_BASE - 4;
    }
    else if(type == HIGH){
        width = 2;
        height = 2;
        y = Y_BASE + 3;
    }
    else{
        width = 2;
        height = 5;
        y = Y_BASE;
    }
}

// 장애물 그리기
void Obstacle::DrawObstacle()
{
    // 이전 위치 지우기
    if (prevX >= 0) {
        for (int i = 0; i < 5; i++){
            Console::SetKeyCursor(prevX, y + i); std::cout << "       ";
        }
    }

    // 장애물 출력
    int checkX = x;
    switch (type)
    {
    case LOW:
        Console::SetKeyCursor(x, y);
        std::cout << "___";
        Console::SetKeyCursor(x, y + 1);
        std::cout << "| |";
        Console::SetKeyCursor(x, y + 2);
        std::cout << "| |";
        Console::SetKeyCursor(x, y + 3);
        std::cout << "| |";
        Console::SetKeyCursor(x, y + 4);
        std::cout << "\\./";
        break;
    case HIGH:
        Console::SetKeyCursor(x, y);
        std::cout << " __ ";
        Console::SetKeyCursor(x, y + 1);
        std::cout << "/__\\";
        break;
    default:
        // 높은 장애물 - 선인장
        Console::SetKeyCursor(x, y);
        std::cout << " \\|/";
        Console::SetKeyCursor(x, y + 1);
        std::cout << "-| |";
        Console::SetKeyCursor(x, y + 2);
        std::cout << " | |-";
        Console::SetKeyCursor(x, y + 3);
        std::cout << "-| |";
        Console::SetKeyCursor(x, y + 4);
        std::cout << " /|\\";
        break;
    }
}

// 화면에서 사라질 위치
bool Obstacle::IsOutOfScreen() { 
    return x <= OBSTACLE_END;
}

// 충돌 박스 리턴
BoundingBox Obstacle::GetBoundingBox() const {
    return {x, y, width, height}; // 장애물 위치 및 크기
}