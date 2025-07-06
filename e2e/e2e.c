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
    const int write_end
) {
    // Redirect stdout to pipe
    if (dup2(write_end, STDOUT_FILENO) == -1) {
        exit(EXIT_FAILURE);
    }
    close(write_end); // Close original write end

    execl(command, command, nullptr);
    exit(EXIT_FAILURE); // Only reached if execl fails
}

#define BUFFER_SIZE 4096

static void read_output_from_pipe(
    const int read_end,
    char *output
) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    char *output_ptr = output;

    while ((bytes_read = read(read_end, buffer, sizeof(buffer) - 1)) > 0) {
        memcpy(output_ptr, buffer, bytes_read);
        output_ptr += bytes_read;
    }

    if (bytes_read == -1) {
        fprintf(stderr, "Error reading from pipe\n");
        close(read_end);
        exit(EXIT_FAILURE);
    }

    *output_ptr = '\0';

    close(read_end);
}

static void capture_output(
    const int read_end,
    const pid_t pid,
    char *output
) {
    read_output_from_pipe(read_end, output);
    int status;
    waitpid(pid, &status, 0);
    if (WEXITSTATUS(status) != EXIT_SUCCESS) {
        fprintf(stderr, "Child process failed with exit code %d\n", WEXITSTATUS(status));
        exit(EXIT_FAILURE);
    }
}

void run_process(const char *command, char *output) {
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
        close(read_end);
        exec_child(command, write_end);
    } else {
        close(write_end);
        capture_output(read_end, pid, output);
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
