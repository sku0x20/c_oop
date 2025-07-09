#include <stdlib.h>

#include "FilePrinter.h"


static int print(FilePrinter *this, const char *message);

static int printerPrint(Printer *const this, const char *message) {
    FilePrinter *filePrinter = (FilePrinter *) this;
    return filePrinter->print(filePrinter, message);
}

static Printer *getPrinter(FilePrinter *const this) {
    return (Printer *) this;
}

static void initPrinterInterface(FilePrinter *const this) {
    this->_printer.print = printerPrint;
    this->printer = getPrinter;
}

static void freeThis(FilePrinter *this);

FilePrinter *NewFilePrinter(FILE *file) {
    FilePrinter *filePrinter = malloc(sizeof(FilePrinter));
    filePrinter->file = file;
    filePrinter->print = print;
    filePrinter->free = freeThis;
    initPrinterInterface(filePrinter);
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
