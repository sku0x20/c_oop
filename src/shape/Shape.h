#pragma once
#include "../printer/Printer.h"

typedef struct ShapeVtable {
    void (*free)(void *this);

    void (*draw)(void *this, Printer *printer);
} ShapeVtable;

typedef struct Shape {
    void *impl;
    ShapeVtable *vtable;

    void (*draw)(struct Shape *this, Printer *printer);

    void (*free)(struct Shape *this);
} Shape;

Shape NewShape(void *ptr, ShapeVtable *vtable);

void freeShapeInternal(Shape *this);

void drawShapeInternal(Shape *this, Printer *printer);
