#include "ManipulatableString.h"

#include <stdlib.h>

static char *cString(ManipulatableString *const this);

ManipulatableString *NewManipulatableString(const char *string) {
    ManipulatableString *manipulatableString = malloc(sizeof(ManipulatableString));
    NewManipulatableStringInto(manipulatableString, string);
    return manipulatableString;
}

void NewManipulatableStringInto(
    ManipulatableString *manipulatableString,
    const char *string
) {
    manipulatableString->string = sdsnew(string);
    manipulatableString->cString = cString;
}

static char *cString(ManipulatableString *const this) {
    return this->string;
}
