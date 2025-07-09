#pragma once

#include "Shape.h"

typedef struct LineShape {
    void (*free)(struct LineShape *this);

    void (*draw)(struct LineShape *this, Printer *printer);
} LineShape;

LineShape *NewLineShape(int len);
