#pragma once

#include "../Shape.h"

typedef struct CustomShape {
    Shape shape1;
    Shape shape2;
    Shape shape3;

    Shape (*shape)(struct CustomShape *this);

    void (*free)(struct CustomShape *this);

    void (*draw)(struct CustomShape *this, Printer *printer);
} CustomShape;

/**
 * shapes are owned by CustomShape
 * move semantics
 */
CustomShape *NewCustomShape(Shape shape1, Shape shape2, Shape shape3);
