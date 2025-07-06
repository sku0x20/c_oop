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

static void read_output_from_pipe(int read_fd, char *output);

static void capture_output(int read_fd, pid_t pid, char *output);

void exec_child(const char *command, int write_fd);

void run_process(const char *command, char *output);

static const char *filePath = nullptr;

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

void exec_child(const char *command, const int write_fd) {
    // Redirect stdout to pipe
    if (dup2(write_fd, STDOUT_FILENO) == -1) {
        exit(EXIT_FAILURE);
    }
    close(write_fd);

    execl(command, command, nullptr);
    exit(EXIT_FAILURE); // Only reached if execl fails
}

#define BUFFER_SIZE 4096

static void read_output_from_pipe(const int read_fd, char *output) {
    char buffer[BUFFER_SIZE] = {0};
    ssize_t bytes_read = 0;
    char *output_ptr = output;
    while ((bytes_read = read(read_fd, buffer, sizeof(buffer) - 1)) > 0) {
        memcpy(output_ptr, buffer, bytes_read);
        output_ptr += bytes_read;
    }
    if (bytes_read == -1) {
        fprintf(stderr, "Error reading from pipe\n");
        close(read_fd);
        exit(EXIT_FAILURE);
    }
    *output_ptr = '\0';
    close(read_fd);
}

static void capture_output(const int read_fd, const pid_t pid, char *output) {
    read_output_from_pipe(read_fd, output);
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
    const int read_fd = pipe_fds[0];
    const int write_fd = pipe_fds[1];

    const pid_t pid = fork();
    if (pid == -1) {
        close(read_fd);
        close(write_fd);
        fprintf(stderr, "Failed to fork\n");
        exit(1);
    }

    if (pid == 0) {
        close(read_fd);
        exec_child(command, write_fd);
    } else {
        close(write_fd);
        capture_output(read_fd, pid, output);
    }
}
