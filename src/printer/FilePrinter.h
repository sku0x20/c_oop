#pragma once
#include <stdio.h>
#include "Printer.h"
#include "debug/Debug.h"

typedef struct FilePrinter {
    Printer _printer;
    Debug _debug;

    FILE *file;

    Printer *(*printer)(struct FilePrinter *this);

    Debug *(*debug)(struct FilePrinter *this);

    void (*free)(struct FilePrinter *this);

    int (*print)(struct FilePrinter *this, const char *message);
} FilePrinter;

FilePrinter *NewFilePrinter(FILE *file);
