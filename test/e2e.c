#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_e2e(void) {
    TEST_ASSERT_TRUE(1);  // Example assertion
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_e2e);
    return UNITY_END();
}