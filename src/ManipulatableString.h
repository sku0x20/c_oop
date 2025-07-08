#pragma once
#include "sds/sds.h"

#include "printer/Printer.h"

typedef struct ManipulatableString {
    sds string;

    char *(*cString)(struct ManipulatableString *const this);

    void (*reverse)(struct ManipulatableString *const this);

    // void (*printTo)(struct StringManipulator *const this, Printer *const printer);
} ManipulatableString;

ManipulatableString *NewManipulatableString(const char *string);

void NewManipulatableStringInto(
    ManipulatableString *manipulatableString,
    const char *string
);
