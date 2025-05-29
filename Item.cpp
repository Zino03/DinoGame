#include "Console.h"
#include "Item.h"
#include <cstdlib>
#include <iostream>

constexpr int ITEM_START_X = 100;
constexpr int ITEM_END_X = 0;
constexpr int ITEM_BASE_Y = 20;
constexpr int ITEM_COLLISION_X = 7;
constexpr int ITEM_WIDTH = 3;
constexpr int ITEM_HEIGHT = 1;

Item::Item()
    : xPos(ITEM_START_X), yPos(ITEM_BASE_Y), prevXPos(ITEM_START_X), active(false), type(SCORE_ITEM) {}

void Item::Spawn() {
    xPos = ITEM_START_X;
    prevXPos = ITEM_START_X;
    yPos = ITEM_BASE_Y + rand() % 4 - 2; // Y 위치 랜덤 (-2~+1 정도 오차)
    type = static_cast<ItemType>(rand() % 3);
    active = true;
}

void Item::Update() {
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

    Console::SetKeyCursor(xPos, yPos);
    switch (type) {
        case SCORE_ITEM: std::cout << "$$$"; break;
        case GAUGE_ITEM: std::cout << "+++"; break;
        case INVINCIBLE_ITEM: std::cout << "***"; break;
    }
}

bool Item::IsOutOfScreen() {
    return xPos <= ITEM_END_X;
}

bool Item::CheckCollision(int dinoX, int dinoY) {
    if (!active) return false;

    // 단순 충돌 범위 판정 (x좌표 범위 겹치고, y좌표가 동일하면 충돌)
    if (xPos < ITEM_COLLISION_X && xPos + ITEM_WIDTH >= dinoX) {
        if (yPos == dinoY || yPos == dinoY - 1) {
            return true;
        }
    }
    return false;
}

bool Item::IsActive() const {
    return active;
}

void Item::Deactivate() {
    active = false;
}

ItemType Item::GetType() const {
    return type;
}
