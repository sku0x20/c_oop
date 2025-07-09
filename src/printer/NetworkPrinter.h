#pragma once
#include "Printer.h"

typedef struct NetworkPrinter {
    Printer printer;

    void (*free)(struct NetworkPrinter *this);

    int (*print)(struct NetworkPrinter *this, const char *message);
} NetworkPrinter;


NetworkPrinter *NewNetworkPrinter();
