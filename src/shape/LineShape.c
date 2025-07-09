#include "LineShape.h"

#include <stdlib.h>


static void drawLine(LineShape *this, Printer *printer);

static void freeThis(LineShape *this);

LineShape *NewLineShape(int len) {
    LineShape *lineShape = malloc(sizeof(LineShape));
    lineShape->draw = drawLine;
    lineShape->free = freeThis;
    return lineShape;
}

static void drawLine(LineShape *const this, Printer *const printer) {
    printer->print(printer, "line");
}

static void freeThis(LineShape *const this) {
    free(this);
}
