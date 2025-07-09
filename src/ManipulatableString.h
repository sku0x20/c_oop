#pragma once
#include "sds/sds.h"

#include "printer/Printer.h"

typedef struct ManipulatableString {
    sds string;

    void (*free)(struct ManipulatableString *this);

    char *(*cString)(struct ManipulatableString *const this);

    void (*reverse)(struct ManipulatableString *const this);

    void (*printTo)(struct ManipulatableString *const this, Printer *const printer);
} ManipulatableString;

ManipulatableString *NewManipulatableString(const char *string);
