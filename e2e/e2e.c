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

/**
 * Runs a process and captures its output
 * @param command Path to the executable to run
 * @return Dynamically allocated string containing the process output (caller must free)
 */
char *run_process(const char *command) {
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

        size_t output_capacity = 0;
        size_t output_size = 0;
        char *output = nullptr;

        // Read child's stdout
        char buffer[4096];
        ssize_t bytes_read;

        // Initial allocation for output buffer
        output_capacity = 4096;
        output = malloc(output_capacity);
        if (!output) {
            close(read_end);
            return nullptr;
        }

        // Read all output
        while ((bytes_read = read(read_end, buffer, sizeof(buffer) - 1)) > 0) {
            // Ensure we have enough space
            if (output_size + bytes_read + 1 > output_capacity) {
                output_capacity *= 2;
                char *new_output = realloc(output, output_capacity);
                if (!new_output) {
                    free(output);
                    close(read_end);
                    return NULL;
                }
                output = new_output;
            }

            // Copy the new data
            memcpy(output + output_size, buffer, bytes_read);
            output_size += bytes_read;
        }

        // Null-terminate the output
        output[output_size] = '\0';

        close(read_end); // Close read end

        int status;
        waitpid(pid, &status, 0);
        if (WEXITSTATUS(status) != 0) {
            free(output);
            return NULL;
        }

        return output;
    }
}

void test_e2e(void) {
    char *output = run_process(filePath);
    TEST_ASSERT_NOT_NULL(output);

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
