#pragma once
#include "Printer.h"

typedef struct NetworkPrinter {
    Printer printer;

    int (*print)(struct NetworkPrinter *this, const char *message);
} NetworkPrinter;


NetworkPrinter *NewNetworkPrinter();
