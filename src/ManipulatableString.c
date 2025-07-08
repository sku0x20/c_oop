#include "ManipulatableString.h"

#include <stdlib.h>

static char *cString(ManipulatableString *const this);

static void reverse(ManipulatableString *const this);

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
    manipulatableString->reverse = reverse;
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
