#include "ManipulatableString.h"

#include <stdlib.h>

static char *cString(ManipulatableString *const this);

static void reverse(ManipulatableString *const this);

static void printTo(ManipulatableString *const this, Printer *const printer);

static void freeThis(ManipulatableString *this);

ManipulatableString *NewManipulatableString(const char *string) {
    ManipulatableString *manipulatableString = malloc(sizeof(ManipulatableString));
    manipulatableString->string = sdsnew(string);
    manipulatableString->cString = cString;
    manipulatableString->reverse = reverse;
    manipulatableString->printTo = printTo;
    manipulatableString->free = freeThis;
    return manipulatableString;
}

static void freeThis(ManipulatableString *const this) {
    sdsfree(this->string);
    free(this);
}

static void printTo(ManipulatableString *const this, Printer *const printer) {
    printer->print(printer, this->string);
}

static char *cString(ManipulatableString *const this) {
    return this->string;
}

static void reverse(ManipulatableString *const this) {
    size_t len = sdslen(this->string);
    sds reversed = sdsempty();
    reversed = sdsgrowzero(reversed, len);
    for (int i = 0; i < len; ++i) {
        reversed[i] = this->string[len - i - 1];
    }
    sdsfree(this->string);
    this->string = reversed;
}
