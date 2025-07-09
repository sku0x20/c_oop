#pragma once
#include <stdio.h>
#include "Printer.h"

typedef struct FilePrinter {
    Printer _printer;

    FILE *file;

    Printer *(*printer)(struct FilePrinter *this);

    void (*free)(struct FilePrinter *this);

    int (*print)(struct FilePrinter *this, const char *message);
} FilePrinter;

FilePrinter *NewFilePrinter(FILE *file);
