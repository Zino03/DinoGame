#ifndef ITEM_H
#define ITEM_H

enum class ItemType {
    ScoreBoost,  // 점수 증가 아이템
    GaugeBoost,  // 게이지 증가 아이템
    Invincibility // 무적 아이템
};

class Item {
private:
    int x, y;            // 아이템 위치
    bool active;         // 화면에 존재하는지
    ItemType type;

public:
    Item();
    void Spawn(int startX, int startY, ItemType itemType); // 아이템 생성
    void Update();  // 아이템 위치 이동 등
    void Draw() const; // 아이템 그리기
    bool IsActive() const;
    void Deactivate();

    int GetX() const;
    int GetY() const;
    ItemType GetType() const;
};
#endif