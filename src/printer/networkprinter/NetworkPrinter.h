#pragma once
#include "../Printer.h"
#include "debug/Debug.h"

typedef struct NetworkPrinter {
    Printer _printer;
    Debug _debug;

    Printer *(*printer)(struct NetworkPrinter *this);

    Debug *(*debug)(struct NetworkPrinter *this);

    void (*free)(struct NetworkPrinter *this);

    int (*print)(struct NetworkPrinter *this, const char *message);
} NetworkPrinter;


NetworkPrinter *NewNetworkPrinter();
