#pragma once
#include <stdio.h>
#include "Printer.h"

typedef struct FilePrinter {
    Printer printer;

    FILE *file;

    int (*print)(struct FilePrinter *const this, const char *message);
} FilePrinter;

FilePrinter *NewFilePrinter(FILE *file);

