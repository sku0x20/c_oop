#include "unity/unity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void setUp(void) {
}

void tearDown(void) {
}

static const char *filePath = nullptr;

void exec_child(
    const char *command,
    const int read_end,
    const int write_end
) {
    close(read_end); // Close read end

    // Redirect stdout to pipe
    if (dup2(write_end, STDOUT_FILENO) == -1) {
        exit(1);
    }
    close(write_end); // Close original write end

    execl(command, command, nullptr);
    exit(1); // Only reached if execl fails
}

char *run_process(const char *command, char *output) {
    int pipe_fds[2];
    if (pipe(pipe_fds) != 0) {
        fprintf(stderr, "Failed to create pipe\n");
        exit(1);
    }
    const int read_end = pipe_fds[0];
    const int write_end = pipe_fds[1];

    const pid_t pid = fork();
    if (pid == -1) {
        close(read_end);
        close(write_end);
        fprintf(stderr, "Failed to fork\n");
        exit(1);
    }

    if (pid == 0) {
        exec_child(command, read_end, write_end);
        return nullptr;
    } else {
        // Parent process

        close(write_end); // Close write end

        // Read child's stdout
        char buffer[4096];
        ssize_t bytes_read;
        char *read_pointer = output;

        while ((bytes_read = read(read_end, buffer, sizeof(buffer) - 1)) > 0) {
            memcpy(read_pointer, buffer, bytes_read);
            read_pointer += bytes_read;
        }
        *read_pointer = '\0';

        close(read_end); // Close read end

        int status;
        waitpid(pid, &status, 0);
        if (WEXITSTATUS(status) != 0) {
            free(output);
            return nullptr;
        }

        return output;
    }
}

void test_e2e(void) {
    char *output = calloc(sizeof(char), 1024 * 16);
    run_process(filePath, output);

    printf("Output from test program:\n%s", output);

    // Add specific assertions on the output if needed
    TEST_ASSERT_NOT_EQUAL(0, strlen(output));

    free(output);
}

int main(int argc, char *argv[]) {
    filePath = argv[1];
    printf("Running E2E tests with file path: %s\n", filePath);

    UNITY_BEGIN();
    RUN_TEST(test_e2e);
    return UNITY_END();
}
