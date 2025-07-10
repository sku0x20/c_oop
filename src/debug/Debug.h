#pragma once

typedef struct DebugVtable {
    void (*print)(void *this);
} DebugVtable;

/**
 * Debug Interface
 */
typedef struct Debug {
    void *impl;
    DebugVtable *vtable;

    void (*print)(struct Debug *this);
} Debug;

Debug NewDebug(void *ptr, DebugVtable *vtable);
