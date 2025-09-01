#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

void stack_init(my_stack_t *stack)
{
    if (stack->data != NULL)
    {
        stack->data = malloc(sizeof(int) * 2);
        stack->capacity = 2;
        stack->length = 0;
    }
}

void stack_clear(my_stack_t *stack)
{
    if (stack->data != NULL)
    {
        free(stack->data);
        stack->data = NULL;
    }
    stack->capacity = 0;
    stack->length = 0;
}

int stack_length(const my_stack_t *stack)
{
    return stack->length;
}

void stack_push(my_stack_t *stack, int value)
{
    if (stack->capacity == 0)
    {
        stack->data = malloc(sizeof(int) * 2);
        stack->capacity = 2;
    }
    if (stack->length >= stack->capacity)
    {
        int *new = realloc(stack->data, sizeof(int) * stack->capacity * 2);
        if (new == NULL)
        {
            fprintf(stderr, "Unable to reallocate stack data.\n");
            exit(1);
        }
        stack->data = new;
        stack->capacity *= 2;
    }
    stack->data[stack->length++] = value;
}

int stack_pop(my_stack_t *stack)
{
    if (stack->length <= 0)
    {
        fprintf(stderr, "Attempted to pop empty stack.\n");
        exit(1);
        return false;
    }
    if (stack->data == NULL)
    {
        fprintf(stderr, "Pop stack attempted to pop NULL data.\n");
        exit(1);
    }
    int ret = stack->data[stack->length - 1];
    stack->length--;
    return ret;
}

int stack_peak(my_stack_t *stack)
{
    return stack->data[stack->length - 1];
}
