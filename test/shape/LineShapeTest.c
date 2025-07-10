#include <stdlib.h>

#include "unity/unity.h"
#include "sds/sds.h"

#include "shape/LineShape.h"
#include "printer/Printer.h"

void setUp(void) {
}

void tearDown(void) {
}

static void getSds();

static void drawLine(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(drawLine);
    RUN_TEST(getSds);
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

    sds pattern = sdsnew("-");
    LineShape *line = NewLineShape(pattern, 10);

    Shape *shape = line->shape(line);
    shape->draw(shape, printer);
    TEST_ASSERT_EQUAL_STRING("----------", printedString);
    shape->free(shape);

    shape = nullptr;
    line = nullptr;

    free(printer);
}

static void getSds() {
    Printer *printer = createFakePrinter();

    sds pattern = sdsnew("-");
    LineShape *line = NewLineShape(pattern, 10);

    sds patternStr = line->getSds(line);
    TEST_ASSERT_EQUAL_STRING("----------", patternStr);

    line->free(line);
    line = nullptr;

    free(printer);
}
