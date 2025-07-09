#include <stdio.h>
#include <stdlib.h>

#include "NetworkPrinter.h"

static int print(NetworkPrinter *this, const char *message);

static int printerPrint(Printer *const this, const char *message) {
    NetworkPrinter *filePrinter = (NetworkPrinter *) this;
    return filePrinter->print(filePrinter, message);
}

static Printer *getPrinter(NetworkPrinter *const this) {
    return (Printer *) this;
}

static void initPrinterInterface(NetworkPrinter *const this) {
    this->printer = getPrinter;
    this->_printer.print = printerPrint;
}

static void freeThis(NetworkPrinter *this);

static void debugPrint(Debug *const this) {
    fprintf(stderr, "debug\n");
}

static Debug *getDebug(NetworkPrinter *const this) {
    char *head = (char *) this;
    head += sizeof(Printer);
    return (Debug *) head;
}

NetworkPrinter *NewNetworkPrinter() {
    NetworkPrinter *networkPrinter = malloc(sizeof(NetworkPrinter));
    networkPrinter->print = print;
    networkPrinter->free = freeThis;
    initPrinterInterface(networkPrinter);
    networkPrinter->_debug.print = debugPrint;
    networkPrinter->debug = getDebug;
    return networkPrinter;
}

static int print(NetworkPrinter *const this, const char *message) {
    fprintf(stdout, "%s", message);
    fflush(stdout);
    return 0;
}

static void freeThis(NetworkPrinter *const this) {
    free(this);
}
