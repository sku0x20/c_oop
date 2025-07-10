#include <stdlib.h>

#include "unity/unity.h"
#include "sds/sds.h"

#include "shape/customshape/CustomShape.h"
#include "printer/Printer.h"
#include "shape/lineshape/LineShape.h"

void setUp(void) {
}

void tearDown(void) {
}

static void drawCustomShape(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(drawCustomShape);
    return UNITY_END();
}

static sds printedString = nullptr;

static int fakePrint(Printer *const printer, const char *message) {
    if (printedString == nullptr) {
        printedString = sdsempty();
    }
    printedString = sdscat(printedString, message);
    return 0;
}

static Printer *createFakePrinter(void) {
    Printer *printer = malloc(sizeof(Printer));
    printer->print = fakePrint;
    return printer;
}

static void drawCustomShape() {
    Printer *printer = createFakePrinter();

    LineShape *line1 = NewLineShape(sdsnew("-"), 1);
    LineShape *line2 = NewLineShape(sdsnew("+"), 3);
    LineShape *line3 = NewLineShape(sdsnew("|"), 5);

    CustomShape *customShape = NewCustomShape(
        line1->shape(line1),
        line2->shape(line2),
        line3->shape(line3)
    );

    Shape shape = customShape->shape(customShape);
    shape.draw(&shape, printer);
    TEST_ASSERT_EQUAL_STRING("-+++|||||", printedString);
    shape.free(&shape);

    line1 = nullptr;
    line2 = nullptr;
    line3 = nullptr;

    free(printer);
}
