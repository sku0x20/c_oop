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

static sds readData(FILE *file);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(printsToFile);
    return UNITY_END();
}

static void printsToFile(void) {
    FILE *tmpFile = tmpfile();

    FilePrinter *filePrinter = NewFilePrinter(tmpFile);
    int result = filePrinter->print(filePrinter, "printing to file: something \n");
    TEST_ASSERT_EQUAL(0, result);

    // sds data = readData(tmpFile);
    // TEST_ASSERT_EQUAL_STRING("printing to file: something \n", data);
    fclose(tmpFile);
}

#define  BUFFER_SIZE  1024

static sds readData(FILE *file) {
    sds data = sdsempty(); {
        size_t n = 0;
        char buffer[BUFFER_SIZE];
        while (true) {
            n = fread(buffer, 1, BUFFER_SIZE, file);
            if (n != BUFFER_SIZE && ferror(file)) {
                fprintf(stderr, "fread error\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
            data = sdscatlen(data, buffer, n);
            if (n != BUFFER_SIZE && feof(file)) {
                data = sdscatlen(data, buffer, n);
                break;
            }
        }
    }
    return data;
}
