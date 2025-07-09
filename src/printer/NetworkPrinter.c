#include <stdio.h>
#include <stdlib.h>

#include "NetworkPrinter.h"

static int print(NetworkPrinter *this, const char *message);

static int printerPrint(Printer *const this, const char *message) {
    NetworkPrinter *filePrinter = (NetworkPrinter *) this;
    return filePrinter->print(filePrinter, message);
}

static void initPrinterInterface(NetworkPrinter *const this) {
    this->printer.print = printerPrint;
}

NetworkPrinter *NewNetworkPrinter() {
    NetworkPrinter *networkPrinter = malloc(sizeof(NetworkPrinter));
    networkPrinter->print = print;
    initPrinterInterface(networkPrinter);
    return networkPrinter;
}

static int print(NetworkPrinter *const this, const char *message) {
    fprintf(stdout, "%s", message);
    fflush(stdout);
    return 0;
}
