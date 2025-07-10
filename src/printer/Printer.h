#pragma once

typedef struct PrinterVtable {
    int (*print)(void *this, const char *message);
} PrinterVtable;

/**
 * Printer Interface
 */
typedef struct Printer {
    void *impl;
    PrinterVtable *vtable;

    int (*print)(struct Printer *this, const char *message);
} Printer;

Printer NewPrinter(void *ptr, PrinterVtable *vtable);
