#pragma once
#include "Printer.h"

typedef struct NetworkPrinter {
    Printer _printer;

    void (*free)(struct NetworkPrinter *this);

    int (*print)(struct NetworkPrinter *this, const char *message);

    // Printer *(*printer)(struct NetworkPrinter *this);
} NetworkPrinter;


NetworkPrinter *NewNetworkPrinter();
