#include "Init.h"

#include <stdio.h>
#include <stdlib.h>

#include "manipulatablestring/ManipulatableString.h"
#include "printer/Printer.h"
#include "printer/networkprinter/NetworkPrinter.h"

void Init(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "usage: 'string'\n");
        exit(EXIT_FAILURE);
    }
    char *input = argv[0];

    NetworkPrinter *np = NewNetworkPrinter();
    Printer printer = np->printer(np);

    ManipulatableString *string = NewManipulatableString(input);
    string->reverse(string);
    string->printTo(string, &printer);
}
