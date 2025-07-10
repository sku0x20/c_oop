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

static uintptr_t calledWith = 0;

void freeImpl(void *this) {
    calledWith = (uintptr_t) this;
}

static uintptr_t printer = 0;

void drawImpl(void *this, Printer *p) {
    calledWith = (uintptr_t) this;
    printer = (uintptr_t) p;
}

static ShapeVtable shapeVtable = {
    .free = freeImpl,
    .draw = drawImpl,
};

void callsImpl() {
    uintptr_t ptr = 0x1234567890;
    Shape shape = NewShape((void *) ptr, &shapeVtable);
    shape.free(&shape);
    TEST_ASSERT_EQUAL(ptr, calledWith);

    calledWith = 0;
    uintptr_t p = 0x9876543210;
    shape.draw(&shape, (Printer *) p);
    TEST_ASSERT_EQUAL(ptr, calledWith);
    TEST_ASSERT_EQUAL(p, printer);
}
