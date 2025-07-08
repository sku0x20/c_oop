#include "Init.h"

#include <stdio.h>
#include <stdlib.h>

#include "ManipulatableString.h"
#include "printer/Printer.h"
#include "printer/NetworkPrinter.h"

void Init(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "usage: 'string'\n");
        exit(EXIT_FAILURE);
    }
    char *input = argv[0];
    ManipulatableString *string = NewManipulatableString(input);
    Printer *printer = (Printer *) NewNetworkPrinter();
    string->printTo(string, printer);
}
