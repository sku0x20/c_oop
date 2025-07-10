#include <stdio.h>
#include <stdlib.h>

#include "unity/unity.h"
#include "sds/sds.h"

#include "printer/networkprinter/NetworkPrinter.h"
#include "printer/Printer.h"
#include "debug/Debug.h"


void setUp(void) {
}

void tearDown(void) {
}

static void printsToStdout(void);

static void viaPrinterInterface(void);

static void printsDebug(void);

static sds readAllData(FILE *file);

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(printsToStdout);
    RUN_TEST(viaPrinterInterface);
    RUN_TEST(printsDebug);
    return UNITY_END();
}

static void printsToStdout(void) {
    freopen("networkPrinter.out.txt", "w+", stdout);

    NetworkPrinter *networkPrinter = NewNetworkPrinter();
    int result = networkPrinter->print(networkPrinter, "printing to stdout: something \n");
    TEST_ASSERT_EQUAL(0, result);

    sds data = readAllData(stdout);
    TEST_ASSERT_EQUAL_STRING("printing to stdout: something \n", data);

    networkPrinter->free(networkPrinter);
    networkPrinter = nullptr;

    fclose(stdout);
}

static void viaPrinterInterface(void) {
    freopen("networkPrinter.out.txt", "w+", stdout);

    NetworkPrinter *networkPrinter = NewNetworkPrinter();

    Printer *printer = networkPrinter->printer(networkPrinter);
    int result = printer->print(printer, "printing to stdout: something \n");
    TEST_ASSERT_EQUAL(0, result);

    sds data = readAllData(stdout);
    TEST_ASSERT_EQUAL_STRING("printing to stdout: something \n", data);

    networkPrinter->free(networkPrinter);
    networkPrinter = nullptr;

    fclose(stdout);
}

static void printsDebug(void) {
    NetworkPrinter *networkPrinter = NewNetworkPrinter();

    Debug debug = networkPrinter->debug(networkPrinter);
    // should print debug statements to stdout
    debug.print(&debug);

    networkPrinter->free(networkPrinter);
    networkPrinter = nullptr;
}

#define  BUFFER_SIZE  1024

static sds readAllData(FILE *file) {
    clearerr(file);
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
