#include "FilePrinter.h"

#include <stdlib.h>

static int print(FilePrinter *const this, const char *message);

FilePrinter *NewFilePrinter(FILE *file) {
    FilePrinter *filePrinter = malloc(sizeof(FilePrinter));
    NewFilePrinterInto(filePrinter, file);
    return filePrinter;
}

void NewFilePrinterInto(
    FilePrinter *filePrinter,
    FILE *file
) {
    filePrinter->file = file;
    filePrinter->print = print;
}

static int print(FilePrinter *const this, const char *message) {
    // fprintf(this->file, "%s", message);
    // fflush(this->file);
    return 0;
}
