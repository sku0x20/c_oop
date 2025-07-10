#pragma once
#include "../printer/Printer.h"

typedef struct ShapeVtable {
    void (*free)(void *this);
} ShapeVtable;

typedef struct Shape {
    void *impl;
    ShapeVtable *vtable;

    void (*draw)(struct Shape *this, Printer *printer);

    void (*free)(struct Shape *this);
} Shape;

Shape NewShape(void *ptr, ShapeVtable *vtable);

void freeShapeInternal(Shape *this);
