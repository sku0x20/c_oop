#include "unity/unity.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void setUp(void) {}
void tearDown(void) {}

static const char *filePath = nullptr;

void test_e2e(void) {
    pid_t pid = fork();
    TEST_ASSERT_NOT_EQUAL(-1, pid);

    if (pid == 0) {
        execl(filePath, filePath, nullptr);
        exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        TEST_ASSERT_EQUAL(0, WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[]) {
    filePath = argv[1];
    printf("Running E2E tests with file path: %s\n", filePath);

    UNITY_BEGIN();
    RUN_TEST(test_e2e);
    return UNITY_END();
}