#pragma once

/**
 * Printer Interface
 */
typedef struct Printer {
    int (*print)(struct Printer *const this, const char *message);
} Printer;
