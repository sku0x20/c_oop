#include "Shape.h"

void freeShapeInternal(Shape *this) {
    const ShapeVtable *vtable = this->vtable;
    void *impl = this->impl;
    vtable->free(impl);
}

Shape NewShape(void *ptr, ShapeVtable *vtable) {
    return (Shape){
        .impl = ptr,
        .vtable = vtable,
        // .draw = vtable->draw,
        .free = freeShapeInternal
    };
}
