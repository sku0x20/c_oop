#pragma once
#include "../printer/Printer.h"

typedef struct Shape {
    void (*draw)(struct Shape *this, Printer *printer);

    void (*free)(struct Shape *this);
} Shape;
