#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

struct BoundingBox {
    int x;
    int y;
    int width;
    int height;

    bool Intersects(const BoundingBox& other) const;
};

#endif
