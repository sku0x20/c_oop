#include "unity/unity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void setUp(void) {}
void tearDown(void) {}

static const char *filePath = nullptr;

void test_e2e(void) {
    int pipe_fds[2];
    int read_end, write_end;

    // Create pipe for stdout capture
    TEST_ASSERT_EQUAL(0, pipe(pipe_fds));
    read_end = pipe_fds[0];
    write_end = pipe_fds[1];

    pid_t pid = fork();
    TEST_ASSERT_NOT_EQUAL(-1, pid);

    if (pid == 0) {
        // Child process
        close(read_end); // Close read end

        // Redirect stdout to pipe
        TEST_ASSERT_NOT_EQUAL(-1, dup2(write_end, STDOUT_FILENO));
        close(write_end); // Close original write end

        execl(filePath, filePath, nullptr);
        exit(1);
    } else {
        // Parent process
        close(write_end); // Close write end

        // Read child's stdout
        char buffer[4096];
        ssize_t bytes_read;

        printf("Output from test program:\n");
        while ((bytes_read = read(read_end, buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            printf("%s", buffer);
        }
        close(read_end); // Close read end

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