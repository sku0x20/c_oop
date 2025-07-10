#include "CustomShape.h"

#include <stdlib.h>

static void drawShape(Shape *const this, Printer *const printer);

static void freeThis(CustomShape *this);

static void freeShape(Shape *this) {
    CustomShape *customShape = (CustomShape *) this;
    freeThis(customShape);
}

static void initShape(CustomShape *const this) {
    this->_shape.draw = drawShape;
    this->_shape.free = freeShape;
}

static Shape *getShape(CustomShape *const this) {
    return (Shape *) this;
}

CustomShape *NewCustomShape(Shape *shape1, Shape *shape2, Shape *shape3) {
    CustomShape *customShape = malloc(sizeof(CustomShape));
    customShape->shape1 = shape1;
    customShape->shape2 = shape2;
    customShape->shape3 = shape3;
    customShape->shape = getShape;
    initShape(customShape);
    return customShape;
}

static void drawShape(Shape *const this, Printer *const printer) {
    CustomShape *customShape = (CustomShape *) this;
    customShape->shape1->draw(customShape->shape1, printer);
    customShape->shape2->draw(customShape->shape2, printer);
    customShape->shape3->draw(customShape->shape3, printer);
}

static void freeThis(CustomShape *const this) {
    this->shape1->free(this->shape1);
    this->shape2->free(this->shape2);
    this->shape3->free(this->shape3);
    free(this);
}
