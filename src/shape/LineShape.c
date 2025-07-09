#include "LineShape.h"

#include <stdlib.h>


static void drawLine(LineShape *this, Printer *printer);

static void freeThis(LineShape *this);

static void drawShape(Shape *const this, Printer *const printer) {
    LineShape *line = (LineShape *) this;
    sds lineString = sdsempty();
    for (int i = 0; i < line->len; ++i) {
        sdscat(lineString, line->pattern);
    }
    printer->print(printer, lineString);
}

static void freeShape(Shape *this) {
    LineShape *line = (LineShape *) this;
    freeThis(line);
}

static void initShape(LineShape *const this) {
    this->_shape.draw = drawShape;
    this->_shape.free = freeShape;
}

static Shape *getShape(LineShape *const this) {
    return (Shape *) this;
}

LineShape *NewLineShape(sds pattern, int len) {
    LineShape *line = malloc(sizeof(LineShape));
    line->pattern = pattern;
    line->len = len;
    line->draw = drawLine;
    line->free = freeThis;
    line->shape = getShape;
    initShape(line);
    return line;
}

static void drawLine(LineShape *const this, Printer *const printer) {
    printer->print(printer, "line");
}

static void freeThis(LineShape *const this) {
    free(this);
}
