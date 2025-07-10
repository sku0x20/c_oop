#include "Printer.h"

static int printInternal(Printer *this, const char *message);

Printer NewPrinter(void *ptr, PrinterVtable *vtable) {
    return (Printer){
        .impl = ptr,
        .vtable = vtable,
        .print = printInternal
    };
}

static int printInternal(Printer *this, const char *message) {
    const PrinterVtable *vtable = this->vtable;
    void *impl = this->impl;
    return vtable->print(impl, message);
}
