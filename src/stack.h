#pragma once

#include <stdbool.h>

typedef struct
{
    int *data;
    int capacity;
    int length;
} my_stack_t;

void stack_init(my_stack_t *stack);
void stack_clear(my_stack_t *stack);

int stack_length(const my_stack_t *stack);
void stack_push(my_stack_t *stack, int value);
int stack_pop(my_stack_t *stack);
int stack_peak(my_stack_t *stack);