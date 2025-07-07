#include "unity/unity.h"

void setUp(void) {
}

void tearDown(void) {
}

static const char *filePath = nullptr;

void test_e2e(void) {
    // printf("Output from test program:\n%s", output);

    // Add specific assertions on the output if needed
    // TEST_ASSERT_NOT_EQUAL(0, strlen(output));
}

int main(int argc, char *argv[]) {
    filePath = argv[1];
    printf("Running E2E tests with file path: %s\n", filePath);

    UNITY_BEGIN();
    RUN_TEST(test_e2e);
    return UNITY_END();
}
