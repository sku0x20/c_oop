#pragma once
#include "Printer.h"

typedef struct NetworkPrinter {
    Printer printer;

    int (*print)(struct NetworkPrinter *const this, const char *message);
} NetworkPrinter;


NetworkPrinter *NewNetworkPrinter();

void NewNetworkPrinterInto(
    NetworkPrinter *networkPrinter
);
