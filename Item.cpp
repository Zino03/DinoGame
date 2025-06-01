#include "Console.h"
#include "Item.h"
#include <cstdlib>
#include <iostream>

constexpr int ITEM_START_X = 100; // 아이템 시작 위치
constexpr int ITEM_END_X = 0; // 아이템이 화면에서 벗어나는 위치
constexpr int ITEM_BASE_Y = 20; // 아이템 y축 위치

Item::Item()
    : x(ITEM_START_X), y(ITEM_BASE_Y), width(1), height(1), prevX(ITEM_START_X), active(false), type(SCORE_ITEM){}

void Item::Spawn() {
    // 생성 x축 위치
    x = ITEM_START_X; 
    prevX = ITEM_START_X;
    y = ITEM_BASE_Y + rand() % 10 - 5; // Y 위치 랜덤 (+-5 정도 오차)
    type = static_cast<ItemType>(rand() % 3); // 3가지 아이템 중 랜덤하게 생성
    active = true; // 아이템 활성화
}

void Item::Update() { // 아이템 위치 이동
    if (!active) return;
    prevX = x; // 이전 위치 저장
    x -= 2; // x축 이동
    if (x < ITEM_END_X) active = false; // 화면에서 사라지면 활성화 해제
}

void Item::DrawItem() {
    if (!active) return;

    // 이전 위치 지우기
    if (prevX >= 0) {
        Console::SetKeyCursor(prevX, y);
        std::cout << "   ";
    }

    // 아이템 그리기
    Console::SetKeyCursor(x, y);
    switch (type) {
        case SCORE_ITEM: std::cout << "$"; break; // 점수 추가
        case GAUGE_ITEM: std::cout << "+"; break; // 게이지 추가
        case INVINCIBLE_ITEM: std::cout << "*"; break; // 무적 상태 
    }
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

// 충돌 박스 리턴
BoundingBox Item::GetBoundingBox() const {
    return {x, y, width, height}; // 장애물 위치 및 크기
}