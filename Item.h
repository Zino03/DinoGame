#ifndef ITEM_H
#define ITEM_H

enum ItemType {
    SCORE_ITEM,
    GAUGE_ITEM,
    INVINCIBLE_ITEM
};

class Item {
private:
    int xPos;
    int yPos;
    int prevXPos;
    bool active;
    ItemType type;

public:
    Item();

    void Spawn();               // 아이템 생성
    void Update();              // 위치 이동
    void DrawItem();            // 아이템 그리기
    bool IsOutOfScreen();       // 화면 밖으로 나갔는지
    bool CheckCollision(int dinoX, int dinoY); // 충돌 판정

    bool IsActive() const;
    void Deactivate();

    ItemType GetType() const;
};
#endif