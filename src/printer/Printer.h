#pragma once

/**
 * Printer Interface
 */
typedef struct Printer {
    int (*print)(struct Printer *this, const char *message);
} Printer;
