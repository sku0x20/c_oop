#include <stdlib.h>

#include "unity/unity.h"

#include "printer/Printer.h"
#include "sds/sds.h"

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
sds calledMsg = nullptr;

int printImpl(void *this, const char *message) {
    calledWith = (uintptr_t) this;
    calledMsg = sdsnew(message);
    return 22;
}

static PrinterVtable printerVTable = {
    .print = printImpl,
};

void callsImpl() {
    uintptr_t ptr = 0x1234567890;
    Printer printer = NewPrinter((void *) ptr, &printerVTable);
    int ret = printer.print(&printer, "test");
    TEST_ASSERT_EQUAL(22, ret);
    TEST_ASSERT_EQUAL(ptr, calledWith);
    TEST_ASSERT_EQUAL_STRING("test", calledMsg);
}
