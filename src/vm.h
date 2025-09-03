#pragma once

#include "stdio.h"
#include "stack.h"

typedef struct {
    size_t pc;
    my_stack_t stack;
} vm_t;

void vm_exit(vm_t *vm, int status);