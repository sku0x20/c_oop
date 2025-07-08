#include "NetworkPrinter.h"

#include <stdio.h>
#include <stdlib.h>

static int print(NetworkPrinter *const this, const char *message);

NetworkPrinter *NewNetworkPrinter() {
    NetworkPrinter *networkPrinter = malloc(sizeof(NetworkPrinter));
    NewNetworkPrinterInto(networkPrinter);
    return networkPrinter;
}

void NewNetworkPrinterInto(
    NetworkPrinter *networkPrinter
) {
    networkPrinter->print = print;
}

static int print(NetworkPrinter *const this, const char *message) {
    fprintf(stdout, "%s", message);
    fflush(stdout);
    return 0;
}
