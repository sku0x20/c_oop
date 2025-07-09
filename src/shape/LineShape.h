#pragma once

#include "Shape.h"

typedef struct LineShape {
    Shape _shape;

    int len;

    Shape *(*shape)(struct LineShape *this);

    void (*free)(struct LineShape *this);

    void (*draw)(struct LineShape *this, Printer *printer);
} LineShape;

LineShape *NewLineShape(int len);
