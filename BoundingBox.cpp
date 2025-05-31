#include "BoundingBox.h"

bool BoundingBox :: Intersects(const BoundingBox& other) const {
        return (x < other.x + other.width &&
            x + width > other.x &&
            y < other.y + other.height &&
            y + height > other.y);
}