#include "unity/unity.h"
#include "sds/sds.h"

#include "ManipulatableString.h"

void setUp(void) {
}

void tearDown(void) {
}

static void reverse(void);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(reverse);
    return UNITY_END();
}

static void reverse(void) {
    ManipulatableString *string = NewManipulatableString("hello world");
    // string->reverse(string);
    TEST_ASSERT_EQUAL_STRING("dlrow olleh", string->cString(string));
}
