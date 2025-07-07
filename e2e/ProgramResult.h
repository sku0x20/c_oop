#pragma once

#include "sds/sds.h"

typedef struct ProgramResult {
    int exitStatus;
    sds output;
} ProgramResult;

ProgramResult runProgram(const char *filepath);
