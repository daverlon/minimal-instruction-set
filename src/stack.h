#pragma once

#include <stdbool.h>

typedef struct
{
    int *data;
    size_t capacity;
    size_t length;
} my_stack_t;

void stack_init(my_stack_t *stack);
void stack_clear(my_stack_t *stack);

int stack_length(const my_stack_t *stack);
void stack_push(my_stack_t *stack, int value);
bool stack_pop(my_stack_t *stack, int *out);
bool stack_peak(my_stack_t *stack, int *out);
bool stack_pick(my_stack_t *stack, size_t n, int *out);