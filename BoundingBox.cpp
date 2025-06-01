#include "BoundingBox.h"

bool BoundingBox :: Intersects(const BoundingBox& other) const {
    // 다른 바운딩 박스와 비교하여, 겹치면 true
        return (x < other.x + other.width && 
            x + width > other.x &&
            y < other.y + other.height &&
            y + height > other.y);
}