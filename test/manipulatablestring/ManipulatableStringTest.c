#include <stdlib.h>

#include "unity/unity.h"
#include "sds/sds.h"

#include "manipulatablestring/ManipulatableString.h"
#include "printer/Printer.h"

void setUp(void) {
}

void tearDown(void) {
}

static void reverse(void);

static void printTo();

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(reverse);
    RUN_TEST(printTo);
    return UNITY_END();
}

static void reverse(void) {
    ManipulatableString *string = NewManipulatableString("hello world");
    string->reverse(string);
    TEST_ASSERT_EQUAL_STRING("dlrow olleh", string->cString(string));
    string->free(string);
    string = nullptr;
}

static sds printedString = nullptr;

int printImpl(void *this, const char *message) {
    TEST_ASSERT_EQUAL(this, (void *) 0x1234567890);
    sdsfree(printedString);
    printedString = sdsnew(message);
    return 0;
}

static PrinterVtable printerVTable = {
    .print = printImpl,
};

static Printer createFakePrinter(void) {
    void *ptr = (void *) 0x1234567890;
    return NewPrinter(ptr, &printerVTable);
}


static void printTo() {
    ManipulatableString *string = NewManipulatableString("hello world via printer");
    Printer printer = createFakePrinter();
    string->printTo(string, printer);
    TEST_ASSERT_EQUAL_STRING("hello world via printer", printedString);
    string->free(string);
    string = nullptr;
}
