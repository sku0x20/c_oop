#include "ManipulatableString.h"

#include <stdlib.h>

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
}
