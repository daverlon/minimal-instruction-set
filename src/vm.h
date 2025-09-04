#pragma once

#include "stdio.h"
#include "stack.h"

typedef struct {
    size_t pc;
    char* file_name;
    size_t file_line;

    my_stack_t data_stack;
    my_stack_t call_stack;
} vm_t;

void vm_abort(vm_t *vm);