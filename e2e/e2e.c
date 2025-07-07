#include "unity/unity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

#include "process.h"

void setUp(void) {
}

void tearDown(void) {
}

static const char *filePath = nullptr;

char **get_lines(const char *output) {
    char **lines = nullptr;
    int line_count = 0;
    char *tmp = strdup(output);
    const char *line = strtok(tmp, "\n");
    while (line != nullptr) {
        lines = realloc(lines, sizeof(char *) * (line_count + 1));
        lines[line_count] = strdup(line);
        line_count++;
        line = strtok(nullptr, "\n");
    }
    free(tmp);
    return lines;
}

void test_e2e(void) {
    char *output = calloc(sizeof(char), 1024 * 16);
    run_process(filePath, output);

    char **lines = get_lines(output);

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
