#include "Console.h"
#include "Item.h"
#include <cstdlib>
#include <iostream>

constexpr int ITEM_START_X = 100; // 아이템 시작 위치
constexpr int ITEM_END_X = 0; // 아이템이 화면에서 벗어나는 위치
constexpr int ITEM_BASE_Y = 20; // 아이템 y축 위치
constexpr int ITEM_COLLISION_X = 7; // 공룡과 x축 충돌

Item::Item()
    : xPos(ITEM_START_X), yPos(ITEM_BASE_Y), prevXPos(ITEM_START_X), active(false), type(SCORE_ITEM), invincibleTime(50){}

void Item::Spawn() {
    xPos = ITEM_START_X;
    prevXPos = ITEM_START_X;
    yPos = ITEM_BASE_Y + rand() % 4 - 2; // Y 위치 랜덤 (+-2 정도 오차)
    type = static_cast<ItemType>(rand() % 3); // 3가지 아이템 중 랜덤하게 생성
    active = true; // 아이템 활성화
}

void Item::Update() { // 아이템 위치 이동
    if (!active) return;
    prevXPos = xPos;
    xPos -= 2;
    if (xPos < ITEM_END_X) active = false;
}

void Item::DrawItem() {
    if (!active) return;

    // 이전 위치 지우기
    if (prevXPos >= 0) {
        Console::SetKeyCursor(prevXPos, yPos);
        std::cout << "   ";
    }

    // 아이템 그리기
    Console::SetKeyCursor(xPos, yPos);
    switch (type) {
        case SCORE_ITEM: std::cout << "$$$"; break;
        case GAUGE_ITEM: std::cout << "+++"; break;
        case INVINCIBLE_ITEM: std::cout << "***"; break;
    }
}

bool Item::CheckCollision(int dinoX, int dinoY) {
    if (!active) return false;

    // 단순 충돌 범위 판정 (x좌표 범위 겹치고, y좌표가 동일하거나 1칸 위에 있으면 충돌)
    if (xPos < ITEM_COLLISION_X && xPos + 3 >= dinoX) { 
        if (yPos == dinoY || yPos == dinoY - 1) {
            return true;
        }
    }
    return false;
}

// 활성화 상태 확인
bool Item::IsActive() const {
    return active; 
}

// 비활성화 처리
void Item::Deactivate() {
    active = false;
}

// 아이템 타입 리턴
ItemType Item::GetType() const {
    return type;
}
