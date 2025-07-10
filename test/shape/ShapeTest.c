#include <stdlib.h>

#include "unity/unity.h"

#include "printer/Printer.h"
#include "shape/Shape.h"

void setUp(void) {
}

void tearDown(void) {
}

void callsImpl(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(callsImpl);
    return UNITY_END();
}

// static Printer *createFakePrinter(void) {
//     Printer *printer = malloc(sizeof(Printer));
//     return printer;
// }

static bool calledFree = false;

void freeImpl(void *this) {
    calledFree = true;
}

static ShapeVtable shapeVtable = {
    .free = freeImpl
};

void callsImpl() {
    // Printer *printer = createFakePrinter();
    uintptr_t ptr = 0x1234567890;
    Shape shape = NewShape((void *) ptr, &shapeVtable);
    shape.free(&shape);
    TEST_ASSERT_TRUE(calledFree);
    // free(printer);
}
