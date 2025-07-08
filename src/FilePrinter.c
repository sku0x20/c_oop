#include "FilePrinter.h"

#include <stdlib.h>

static void initPrinterInterface(FilePrinter *const this);

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
    initPrinterInterface(filePrinter);
}

static int printerPrint(Printer *const this, const char *message) {
    FilePrinter *filePrinter = (FilePrinter *) this;
    return filePrinter->print(filePrinter, message);
}

static void initPrinterInterface(FilePrinter *const this) {
    this->printer.print = printerPrint;
}


static int print(FilePrinter *const this, const char *message) {
    fprintf(this->file, "%s", message);
    fflush(this->file);
    return 0;
}
