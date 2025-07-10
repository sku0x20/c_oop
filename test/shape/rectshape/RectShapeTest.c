#include <stdlib.h>

#include "unity/unity.h"
#include "sds/sds.h"

#include "shape/rectshape/RectShape.h"
#include "printer/Printer.h"

void setUp(void) {
}

void tearDown(void) {
}

static void drawRect(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(drawRect);
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

static void drawRect() {
    Printer *printer = createFakePrinter();

    RectShape *rect = NewRectShape(5, 3);

    Shape shape = rect->shape(rect);
    shape.draw(&shape, printer);
    // +---+
    // |   |
    // +---+
    TEST_ASSERT_EQUAL_STRING("+---+\n|   |\n+---+\n", printedString);
    shape.free(&shape);

    rect = nullptr;

    free(printer);
}
