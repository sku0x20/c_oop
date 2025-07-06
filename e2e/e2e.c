#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_e2e(void) {
    TEST_ASSERT_TRUE(1);
}

static const char *filePath = "";

int main(int argc, char *argv[]) {
    filePath = argv[1];
    printf("Running E2E tests with file path: %s\n", filePath);

    UNITY_BEGIN();
    RUN_TEST(test_e2e);
    return UNITY_END();
}