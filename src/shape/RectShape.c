#include "RectShape.h"

#include "sds/sds.h"

#include <stdlib.h>

void drawRect(RectShape *this, Printer *printer);

void drawShape(Shape *const this, Printer *const printer) {
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
    return rectShape;
}

void drawRect(RectShape *this, Printer *printer) {
    sds rectString = sdsempty();

    sdscat(rectString, "+");
    for (int j = 1; j < this->width - 1; ++j) {
        sdscat(rectString, "-");
    }
    sdscat(rectString, "+");
    sdscat(rectString, "\n");

    for (int i = 1; i < this->height - 1; ++i) {
        sdscat(rectString, "|");
        for (int j = 1; j < this->width - 1; ++j) {
            sdscat(rectString, " ");
        }
        sdscat(rectString, "|");
        sdscat(rectString, "\n");
    }

    sdscat(rectString, "+");
    for (int j = 1; j < this->width - 1; ++j) {
        sdscat(rectString, "-");
    }
    sdscat(rectString, "+");
    sdscat(rectString, "\n");

    printer->print(printer, rectString);
}
