#ifndef ITEM_H
#define ITEM_H

enum ItemType {
    SCORE_ITEM, // 점수 증가
    GAUGE_ITEM, // 게이지 증가
    INVINCIBLE_ITEM // 무적
};

// 아이템 관리
class Item {
private:
    // 현재 아이템 위치와 이전 위치(지우기 용도)
    int xPos;
    int yPos;
    int prevXPos;
    bool active; // 아이템 활성화 여부
    ItemType type;
    int invincibleTime;

public:
    Item();

    void Spawn();               // 아이템 생성
    void Update();              // 위치 이동
    void DrawItem();            // 아이템 그리기
    bool CheckCollision(int dinoX, int dinoY); // 충돌 판정

    // 아이템 상태 관리
    bool IsActive() const;
    void Deactivate();

    ItemType GetType() const; // 아이템 타입 반환
};
#endif