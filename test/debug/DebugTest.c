#include <stdlib.h>

#include "unity/unity.h"

#include "debug/Debug.h"

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

void printImpl(void *this) {
    calledWith = (uintptr_t) this;
}

static DebugVtable debugVtable = {
    .print = printImpl,
};

void callsImpl() {
    uintptr_t ptr = 0x1234567890;
    Debug debug = NewDebug((void *) ptr, &debugVtable);
    debug.print(&debug);
    TEST_ASSERT_EQUAL(ptr, calledWith);
}
