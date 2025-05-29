#include "Item.h"
#include "Console.h"
#include <cstdlib>
#include <iostream>

Item::Item() : x(0), y(0), active(false), type(ItemType::ScoreBoost) {}

void Item::Spawn(int startX, int startY, ItemType itemType) {
    x = startX;
    y = startY;
    type = itemType;
    active = true;
}

void Item::Update() {
    if (!active) return;
    x--;  // 왼쪽으로 이동
    if (x < 0) active = false;  // 화면 벗어나면 비활성화
}

void Item::Draw() const {
    if (!active) return;
    Console::SetKeyCursor(x, y);
    switch(type) {
        case ItemType::ScoreBoost:
            std::cout << "$"; // 점수 아이템 심볼
            break;
        case ItemType::GaugeBoost:
            std::cout << "G"; // 게이지 아이템 심볼
            break;
        case ItemType::Invincibility:
            std::cout << "I"; // 무적 아이템 심볼
            break;
    }
}

bool Item::IsActive() const { return active; }
void Item::Deactivate() { active = false; }
int Item::GetX() const { return x; }
int Item::GetY() const { return y; }
ItemType Item::GetType() const { return type; }
