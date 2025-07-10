#include <stdlib.h>

#include "FilePrinter.h"


static void freeThis(FilePrinter *this);

static int print(FilePrinter *this, const char *message);

static PrinterVtable printerVtable = {
    .print = (void *) print,
};

static Printer getPrinter(FilePrinter *const this) {
    return NewPrinter(this, &printerVtable);
}

static void debugPrint(FilePrinter *const this) {
    fprintf(stderr, "Debug FilePrinter = %p\n", this);
    fprintf(stderr, "debug file = %p\n", this->file);
}

static DebugVtable debugVtable = {
    .print = (void *) debugPrint,
};

static Debug getDebug(FilePrinter *const this) {
    return NewDebug(this, &debugVtable);
}

FilePrinter *NewFilePrinter(FILE *file) {
    FilePrinter *filePrinter = malloc(sizeof(FilePrinter));
    filePrinter->file = file;
    filePrinter->print = print;
    filePrinter->free = freeThis;
    filePrinter->debug = getDebug;
    filePrinter->printer = getPrinter;
    return filePrinter;
}

static void freeThis(FilePrinter *const this) {
    fclose(this->file);
    free(this);
}

static int print(FilePrinter *const this, const char *message) {
    fprintf(this->file, "%s", message);
    fflush(this->file);
    return 0;
}
