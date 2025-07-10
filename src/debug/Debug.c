#include "Debug.h"


static void printInternal(Debug *this);

Debug NewDebug(void *ptr, DebugVtable *vtable) {
    return (Debug){
        .impl = ptr,
        .vtable = vtable,
        .print = printInternal
    };
}

static void printInternal(Debug *this) {
    const DebugVtable *vtable = this->vtable;
    void *impl = this->impl;
    vtable->print(impl);
}
