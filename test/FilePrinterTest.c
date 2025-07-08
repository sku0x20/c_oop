#include "FilePrinter.h"
#include "libs/unity/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sds/sds.h"

void setUp(void) {
}

void tearDown(void) {
}

static void printsToFile(void);

static sds readAllData(FILE *file);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(printsToFile);
    return UNITY_END();
}

static void printsToFile(void) {
    // FILE *tmpFile = tmpfile();
    FILE *tmpFile = fopen("./test.txt", "w+");

    FilePrinter *filePrinter = NewFilePrinter(tmpFile);
    int result = filePrinter->print(filePrinter, "printing to file: something \n");
    TEST_ASSERT_EQUAL(0, result);

    sds data = readAllData(tmpFile);
    printf("data = '%s' \n", data);
    // TEST_ASSERT_EQUAL_STRING("printing to file: something \n", data);
    fclose(tmpFile);
}

#define  BUFFER_SIZE  1024

static sds readAllData(FILE *file) {
    fseek(file, 0, SEEK_SET);
    sds data = sdsempty(); {
        size_t n = 0;
        char buffer[BUFFER_SIZE];
        while (true) {
            n = fread(buffer, 1, BUFFER_SIZE, file);
            printf("n = %zu\n", n);
            if (n != BUFFER_SIZE && ferror(file)) {
                fprintf(stderr, "fread error\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            data = sdscatlen(data, buffer, n);
            if (n != BUFFER_SIZE && feof(file)) {
                break;
            }
        }
    }
    return data;
}
