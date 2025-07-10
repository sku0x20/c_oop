#include <stdio.h>
#include <stdlib.h>

#include "NetworkPrinter.h"

static int print(NetworkPrinter *this, const char *message);

static void freeThis(NetworkPrinter *this);

static void debugPrint(NetworkPrinter *const this) {
    fprintf(stderr, "Debug NetworkPrinter = %p\n", this);
}

static DebugVtable debugVtable = {
    .print = (void *) debugPrint,
};

static Debug getDebug(NetworkPrinter *const this) {
    return NewDebug(this, &debugVtable);
}

static PrinterVtable printerVtable = {
    .print = (void *) print,
};

static Printer getPrinter(NetworkPrinter *const this) {
    return NewPrinter(this, &printerVtable);
}

NetworkPrinter *NewNetworkPrinter() {
    NetworkPrinter *networkPrinter = malloc(sizeof(NetworkPrinter));
    networkPrinter->print = print;
    networkPrinter->free = freeThis;
    networkPrinter->printer = getPrinter;
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
