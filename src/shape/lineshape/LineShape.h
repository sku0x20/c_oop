#pragma once

#include "../Shape.h"
#include "sds/sds.h"


typedef struct LineShape {
    sds pattern;
    int len;

    Shape (*shape)(struct LineShape *this);

    void (*free)(struct LineShape *this);

    void (*draw)(struct LineShape *this, Printer *printer);

    sds (*getSds)(struct LineShape *this);
} LineShape;

/**
 * pattern is owned by LineShape
 * move semantics
 */
LineShape *NewLineShape(sds pattern, int len);
