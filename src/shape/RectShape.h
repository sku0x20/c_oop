#pragma once

#include "Shape.h"
#include "sds/sds.h"


typedef struct Rect {
    Shape _shape;

    int width;
    int height;
    sds drawn;

    Shape *(*shape)(struct Rect *this);
} RectShape;

RectShape *NewRectShape(int width, int height);
