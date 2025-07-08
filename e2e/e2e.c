#include "Program.h"
#include "unity/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

static const char *filePath = nullptr;

void printsReversedStdout(void) {
    const ProgramResult result = runProgram(filePath, "this should be reversed;;;");
    TEST_ASSERT_EQUAL(0, result.exitStatus);
    TEST_ASSERT_EQUAL_STRING(";;;desrever eb dluohs siht", result.output);
}

int main(int argc, char *argv[]) {
    filePath = argv[1];
    UNITY_BEGIN();
    RUN_TEST(printsReversedStdout);
    return UNITY_END();
}
