#include "RectShape.h"

#include <stdlib.h>

#include "../lineshape/LineShape.h"

static void drawShapeAndStore(RectShape *this);

static void drawRect(RectShape *this, Printer *printer);

static void drawShape(Shape *const this, Printer *const printer) {
    RectShape *rect = (RectShape *) this;
    drawRect(rect, printer);
}

static void initShape(RectShape *const this) {
    this->_shape.draw = drawShape;
}

static Shape *getShape(RectShape *const this) {
    return (Shape *) this;
}

RectShape *NewRectShape(int width, int height) {
    RectShape *rectShape = malloc(sizeof(RectShape));
    rectShape->width = width;
    rectShape->height = height;
    rectShape->shape = getShape;
    initShape(rectShape);
    drawShapeAndStore(rectShape);
    return rectShape;
}

void drawRect(RectShape *const this, Printer *const printer) {
    printer->print(printer, this->drawn);
}

void drawShapeAndStore(RectShape *this) {
    sds rectString = sdsempty();

    LineShape *plus = NewLineShape(sdsnew("+"), 1);
    LineShape *minus = NewLineShape(sdsnew("-"), this->width - 2);
    LineShape *pipe = NewLineShape(sdsnew("|"), 1);
    LineShape *space = NewLineShape(sdsnew(" "), this->width - 2);
    LineShape *newLine = NewLineShape(sdsnew("\n"), 1);

    rectString = sdscat(rectString, plus->getSds(plus));
    rectString = sdscat(rectString, minus->getSds(minus));
    rectString = sdscat(rectString, plus->getSds(plus));
    rectString = sdscat(rectString, newLine->getSds(newLine));

    for (int i = 0; i < this->height - 2; ++i) {
        rectString = sdscat(rectString, pipe->getSds(pipe));
        rectString = sdscat(rectString, space->getSds(space));
        rectString = sdscat(rectString, pipe->getSds(pipe));
        rectString = sdscat(rectString, newLine->getSds(newLine));
    }

    rectString = sdscat(rectString, plus->getSds(plus));
    rectString = sdscat(rectString, minus->getSds(minus));
    rectString = sdscat(rectString, plus->getSds(plus));
    rectString = sdscat(rectString, newLine->getSds(newLine));

    this->drawn = rectString;

    plus->free(plus);
    minus->free(minus);
    pipe->free(pipe);
    space->free(space);
}
