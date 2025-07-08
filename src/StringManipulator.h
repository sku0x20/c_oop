#pragma once
#include "sds/sds.h"

#include "printer/Printer.h"

typedef struct StringManipulator {
    sds string;

    // void (*printTo)(struct StringManipulator *const this, Printer *const printer);
} StringManipulator;

StringManipulator *NewStringManipulator(const char *string);

void NewStringManipulatorInto(
    StringManipulator *manipulator,
    const char *string
);
