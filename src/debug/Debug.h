#pragma once

/**
 * Debug Interface
 */
typedef struct Debug {
    void (*print)(struct Debug *this);
} Debug;
