#pragma once
#include "Printer.h"

typedef struct NetworkPrinter {
    Printer _printer;

    Printer *(*printer)(struct NetworkPrinter *this);


    void (*free)(struct NetworkPrinter *this);

    int (*print)(struct NetworkPrinter *this, const char *message);
} NetworkPrinter;


NetworkPrinter *NewNetworkPrinter();
