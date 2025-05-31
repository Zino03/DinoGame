#include "BoundingBox.h"

bool BoundingBox :: Intersects(const BoundingBox& other) const {
        return !(x + width < other.x || other.x + other.width < x ||
                 y + height < other.y || other.y + other.height < y);
}