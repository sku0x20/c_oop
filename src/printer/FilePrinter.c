#include <stdlib.h>

#include "FilePrinter.h"


static int print(FilePrinter *const this, const char *message);

static int printerPrint(Printer *const this, const char *message) {
    FilePrinter *filePrinter = (FilePrinter *) this;
    return filePrinter->print(filePrinter, message);
}

static void initPrinterInterface(FilePrinter *const this) {
    this->printer.print = printerPrint;
}

FilePrinter *NewFilePrinter(FILE *file) {
    FilePrinter *filePrinter = malloc(sizeof(FilePrinter));
    filePrinter->file = file;
    filePrinter->print = print;
    initPrinterInterface(filePrinter);
    return filePrinter;
}

static int print(FilePrinter *const this, const char *message) {
    fprintf(this->file, "%s", message);
    fflush(this->file);
    return 0;
}
