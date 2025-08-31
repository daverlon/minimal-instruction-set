#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "instruction.h"

struct my_stack_t;

int pop_value(my_stack_t *stack)
{
    int value = 0;
    bool success = stack_pop(stack, &value);
    if (!success)
    {
        stack_clear(stack);
        exit(1);
    }
    return value;
    ;
}

void execute_instruction(my_stack_t *stack, struct instruction instr)
{
    switch (instr.cmd)
    {
    case CMD_PUSH:
        stack_push(stack, instr.value);
        break;
    case CMD_ADD:
    {
        stack_push(stack, pop_value(stack) + pop_value(stack));
        break;
    }
    case CMD_SUB:
    {
        int a = pop_value(stack);
        int b = pop_value(stack);
        stack_push(stack, b - a);
        break;
    }
    case CMD_MUL:
    {
        stack_push(stack, pop_value(stack) * pop_value(stack));
        break;
    }
    case CMD_DIV:
    {
        int a = pop_value(stack);
        int b = pop_value(stack);
        stack_push(stack, b / a);
        break;
    }
    case CMD_PRINT:
        fprintf(stdout, "%d\n", pop_value(stack));
        break;
    default:
        fprintf(stderr, "Invalid instruction command.\n");
        break;
    }
}