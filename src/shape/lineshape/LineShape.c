#include "LineShape.h"

#include <stdio.h>
#include <stdlib.h>


static sds getSds(LineShape *this);

static void drawLine(LineShape *this, Printer *printer);

static void freeThis(LineShape *this);

static ShapeVtable _shapeVtable = {
    .free = (void *) freeThis,
    .draw = (void *) drawLine
};

static Shape getShape(LineShape *const this) {
    return NewShape(this, &_shapeVtable);
}

LineShape *NewLineShape(sds pattern, int len) {
    LineShape *line = malloc(sizeof(LineShape));
    line->pattern = pattern;
    line->len = len;
    line->draw = drawLine;
    line->free = freeThis;
    line->getSds = getSds;
    line->shape = getShape;
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
