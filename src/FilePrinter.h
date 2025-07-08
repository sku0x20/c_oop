#pragma once
#include <stdio.h>

typedef struct FilePrinter {
    FILE *file;

    int (*print)(struct FilePrinter *const this, const char *message);
} FilePrinter;

FilePrinter *NewFilePrinter(FILE *file);

void NewFilePrinterInto(
    FilePrinter *filePrinter,
    FILE *file
);
