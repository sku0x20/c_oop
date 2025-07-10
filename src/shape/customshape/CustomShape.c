#include "CustomShape.h"

#include <stdlib.h>

static void drawShape(CustomShape *const this, Printer *const printer);

static void freeThis(CustomShape *this);

static ShapeVtable _shapeVtable = {
    .free = (void *) freeThis,
    .draw = (void *) drawShape
};

static Shape getShape(CustomShape *const this) {
    return NewShape(this, &_shapeVtable);
}

CustomShape *NewCustomShape(Shape shape1, Shape shape2, Shape shape3) {
    CustomShape *customShape = malloc(sizeof(CustomShape));
    customShape->shape1 = shape1;
    customShape->shape2 = shape2;
    customShape->shape3 = shape3;
    customShape->shape = getShape;
    return customShape;
}

static void drawShape(CustomShape *const this, Printer *const printer) {
    this->shape1.draw(&this->shape1, printer);
    this->shape2.draw(&this->shape2, printer);
    this->shape3.draw(&this->shape3, printer);
}

static void freeThis(CustomShape *const this) {
    this->shape1.free(&this->shape1);
    this->shape2.free(&this->shape2);
    this->shape3.free(&this->shape3);
    free(this);
}
