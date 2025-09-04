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
    if (stack->capacity == 0 || stack->data == NULL)
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

bool stack_pop(my_stack_t *stack, int *out)
{
    if (stack->length <= 0)
    {
        fprintf(stderr, "Attempted to pop empty stack.\n");
        return false;
    }
    if (stack->data == NULL)
    {
        fprintf(stderr, "Pop stack attempted to pop NULL data.\n");
        return false;
    }
    *out = stack->data[stack->length - 1];
    stack->length--;
    return true;
}

bool stack_peak(my_stack_t *stack, int *out)
{
    if (stack->length <= 0)
    {
        fprintf(stderr, "Attempted to peak empty stack.\n");
        return false;
    }
    *out = stack->data[stack->length - 1];
    return true;
}

bool stack_pick(my_stack_t *stack, size_t n, int *out)
{
    if (stack->length - 1 < n || n < 0) 
    {
        fprintf(stderr, "Attempted to pick item at position %zu from the top.\n", n);
        fprintf(stderr, "Stack length is %zu\n", stack->length);
        return false;
    }
    *out = stack->data[stack->length - n - 1];
    return true;
}