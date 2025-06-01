#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

// 충돌 판정을 위한 바운딩 박스 클래스 (Dino, Obstacle, Item에 적용)
struct BoundingBox {
    int x, y; // x축 위치, y축 위치
    int width, height; // 너비, 높이

    bool Intersects(const BoundingBox& other) const; // 충돌 감지
};

#endif
