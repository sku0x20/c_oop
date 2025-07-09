#pragma once

#include "Shape.h"

typedef struct Rect {
    Shape _shape;

    int width;
    int height;

    Shape *(*shape)(struct Rect *this);
} RectShape;

RectShape *NewRectShape(int width, int height);
