#pragma once
#include "sds/sds.h"

#include "../printer/Printer.h"

typedef struct ManipulatableString {
    sds string;

    void (*free)(struct ManipulatableString *this);

    char *(*cString)(struct ManipulatableString *this);

    void (*reverse)(struct ManipulatableString *this);

    void (*printTo)(struct ManipulatableString *this, Printer printer);
} ManipulatableString;

ManipulatableString *NewManipulatableString(const char *string);
