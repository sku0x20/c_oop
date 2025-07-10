#include "Shape.h"

static void freeShapeInternal(Shape *this);

static void drawShapeInternal(Shape *this, Printer *printer);

Shape NewShape(void *ptr, ShapeVtable *vtable) {
    return (Shape){
        .impl = ptr,
        .vtable = vtable,
        .draw = drawShapeInternal,
        .free = freeShapeInternal
    };
}

static void freeShapeInternal(Shape *this) {
    const ShapeVtable *vtable = this->vtable;
    void *impl = this->impl;
    vtable->free(impl);
}

static void drawShapeInternal(Shape *this, Printer *printer) {
    const ShapeVtable *vtable = this->vtable;
    void *impl = this->impl;
    vtable->draw(impl, printer);
}
