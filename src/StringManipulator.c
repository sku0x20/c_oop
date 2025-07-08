#include "StringManipulator.h"

#include <stdlib.h>

StringManipulator *NewStringManipulator(const char *string) {
    StringManipulator *manipulator = malloc(sizeof(StringManipulator));
    NewStringManipulatorInto(manipulator, string);
    return manipulator;
}

void NewStringManipulatorInto(
    StringManipulator *manipulator,
    const char *string
) {
    manipulator->string = sdsnew(string);
}
