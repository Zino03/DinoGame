#include "Obstacle.h"
#include "Console.h"
#include <iostream>
#include <cstdlib> 

constexpr int Y_BASE = 20;
constexpr int TREE_START = 100;
constexpr int TREE_END = 0;
constexpr int TREE_COLLISION = 7;
constexpr int Y_COLLISION = 5;

Obstacle::Obstacle() : nTreePos(TREE_START), prevXPos(TREE_START) {
    type = (rand() % 2 == 0) ? LOW_TREE : HIGH_TREE;
}

// 나무 위치
void Obstacle::Update()
{
    prevXPos = nTreePos;
    if (nTreePos > TREE_END)
        nTreePos -= 2; // 왼쪽으로 이동
    else{
        nTreePos = TREE_START;
        type = (rand() % 2 == 0) ? LOW_TREE : HIGH_TREE; // 오른쪽 끝에서 생성
    }
}

// 나무 그리기
void Obstacle::DrawTree()
{
    // 이전 위치 지우기
    if (prevXPos >= 0) {
        Console::SetKeyCursor(prevXPos, Y_BASE - 1); std::cout << "       ";
        Console::SetKeyCursor(prevXPos, Y_BASE); std::cout << "       ";
        Console::SetKeyCursor(prevXPos, Y_BASE + 1); std::cout << "       ";
        Console::SetKeyCursor(prevXPos, Y_BASE + 2); std::cout << "       ";
        Console::SetKeyCursor(prevXPos, Y_BASE + 3); std::cout << "       ";
        Console::SetKeyCursor(prevXPos, Y_BASE + 4); std::cout << "       ";
    }

    int x = nTreePos;
        if (type == LOW_TREE) {
        // 상단 장애물 (슬라이딩 필요)
        for (int i = 0; i < 2; i++) {
            Console::SetKeyCursor(x, Y_BASE - i);
            std::cout << "ooo" << "\n";
        }
    }
    else {
        // 하단 장애물 (점프 필요)
        for (int i = 0; i < 4; i++) {
            Console::SetKeyCursor(x, Y_BASE + i);
            std::cout << "ooo" << "\n";
        }
    }
}

bool Obstacle::IsOutOfScreen() {
    return nTreePos <= TREE_END;
}

// 충돌 여부 확인
bool Obstacle::CheckCollision(int dinoY, bool isSliding)
{
    // 공룡의 실제 콘솔 y위치 (머리 기준)
    int dinoYPos = Y_BASE - dinoY;

    if (nTreePos < TREE_COLLISION && nTreePos > TREE_END + 1) {
        if (type == LOW_TREE) {
            // 슬라이딩 중이면 통과
            return !isSliding;
        } 
        else if (type == HIGH_TREE) {
            // 공룡 머리가 장애물 하단에 닿으면 충돌
            return dinoYPos >= Y_BASE; // 4칸짜리 높은 나무: y 20~23
        }
    }
    return false;
}

