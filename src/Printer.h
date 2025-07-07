#pragma once

/**
 * Printer Interface
 */
typedef struct Printer {
    int (*print)(const char *message);
} Printer;
