#include "Shape.h"

Shape NewShape(void *ptr, ShapeVtable *vtable) {
    return (Shape){
        .impl = ptr,
        .vtable = vtable,
        .draw = drawShapeInternal,
        .free = freeShapeInternal
    };
}

void freeShapeInternal(Shape *this) {
    const ShapeVtable *vtable = this->vtable;
    void *impl = this->impl;
    vtable->free(impl);
}

void drawShapeInternal(Shape *this, Printer *printer) {
    const ShapeVtable *vtable = this->vtable;
    void *impl = this->impl;
    vtable->draw(impl, printer);
}
