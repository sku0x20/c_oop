#include "Init.h"

#include <stdio.h>
#include <stdlib.h>

#include "ManipulatableString.h"
#include "printer/Printer.h"
#include "printer/NetworkPrinter.h"

void Init(char *argv[], int argc) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *input = argv[1];
    ManipulatableString *string = NewManipulatableString(input);
    Printer *printer = (Printer *) NewNetworkPrinter();
    string->printTo(string, printer);
}
