#include "LineShape.h"

#include <stdio.h>
#include <stdlib.h>


static sds getSds(LineShape *const this);

static void drawLine(LineShape *this, Printer *printer);

static void freeThis(LineShape *this);

static void drawShape(Shape *const this, Printer *const printer) {
    LineShape *line = (LineShape *) this;
    drawLine(line, printer);
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
    line->getSds = getSds;
    line->shape = getShape;
    initShape(line);
    return line;
}

static void drawLine(LineShape *const this, Printer *const printer) {
    sds lineString = getSds(this);
    printer->print(printer, lineString);
    sdsfree(lineString);
}

static sds getSds(LineShape *const this) {
    sds lineString = sdsempty();
    for (int i = 0; i < this->len; ++i) {
        lineString = sdscat(lineString, this->pattern);
    }
    return lineString;
}

static void freeThis(LineShape *const this) {
    sdsfree(this->pattern);
    free(this);
}
