#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libs/unity/unity.h"
#include "sds/sds.h"

#include "printer/fileprinter/FilePrinter.h"
#include "printer/Printer.h"
#include "debug/Debug.h"


void setUp(void) {
}

void tearDown(void) {
}

static void printsToFile(void);

static void viaPrinterInterface(void);

static void printsDebug(void);

static sds readAllData(FILE *file);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(printsToFile);
    RUN_TEST(viaPrinterInterface);
    RUN_TEST(printsDebug);
    return UNITY_END();
}

static void printsToFile(void) {
    FILE *tmpFile = tmpfile();

    FilePrinter *filePrinter = NewFilePrinter(tmpFile);
    int result = filePrinter->print(filePrinter, "printing to file: something \n");
    TEST_ASSERT_EQUAL(0, result);

    sds data = readAllData(tmpFile);
    TEST_ASSERT_EQUAL_STRING("printing to file: something \n", data);

    // this will close the tmpFile
    filePrinter->free(filePrinter);
    filePrinter = nullptr;
}

static void viaPrinterInterface(void) {
    FILE *tmpFile = tmpfile();

    FilePrinter *filePrinter = NewFilePrinter(tmpFile);

    Printer *printer = filePrinter->printer(filePrinter);
    int result = printer->print(printer, "printing to file: something \n");
    TEST_ASSERT_EQUAL(0, result);

    sds data = readAllData(tmpFile);
    TEST_ASSERT_EQUAL_STRING("printing to file: something \n", data);

    // this will close the tmpFile
    filePrinter->free(filePrinter);
    filePrinter = nullptr;
}

static void printsDebug(void) {
    FilePrinter *filePrinter = NewFilePrinter(stdout);

    Debug debug = filePrinter->debug(filePrinter);
    // should print debug statements to stderr
    debug.print(&debug);

    filePrinter->free(filePrinter);
    filePrinter = nullptr;
}

#define  BUFFER_SIZE  1024

static sds readAllData(FILE *file) {
    fseek(file, 0, SEEK_SET);
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
                break;
            }
        }
    }
    return data;
}
