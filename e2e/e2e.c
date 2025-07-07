#include "ProgramResult.h"
#include "unity/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

static const char *filePath = nullptr;

void test_e2e(void) {
    const ProgramResult result = runProgram(filePath);
    TEST_ASSERT_EQUAL(0, result.exitStatus);
    TEST_ASSERT_EQUAL_STRING("running coop\nsome error!!!\n", result.output);
}

int main(int argc, char *argv[]) {
    filePath = argv[1];
    UNITY_BEGIN();
    RUN_TEST(test_e2e);
    return UNITY_END();
}
