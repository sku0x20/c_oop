#include <stdlib.h>

#include "unity/unity.h"
#include "sds/sds.h"

#include "shape/LineShape.h"
#include "printer/Printer.h"

void setUp(void) {
}

void tearDown(void) {
}

static void drawLine(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(drawLine);
    return UNITY_END();
}

static sds printedString = nullptr;

static int fakePrint(Printer *const printer, const char *message) {
    sdsfree(printedString);
    printedString = sdsnew(message);
    return 0;
}

static Printer *createFakePrinter(void) {
    Printer *printer = malloc(sizeof(Printer));
    printer->print = fakePrint;
    return printer;
}

static void drawLine() {
    Printer *printer = createFakePrinter();

    LineShape *line = NewLineShape(10);
    // line->draw(line, printer);
    // TEST_ASSERT_EQUAL_STRING("----------", printedString);
    line->free(line);
    line = nullptr;

    free(printer);
}
