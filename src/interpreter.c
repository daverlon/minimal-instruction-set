#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "instruction.h"

void execute_instruction(vm_t *vm, const instruction_t instr)
{
    my_stack_t *stack = &vm->stack;

    switch (instr.cmd)
    {
    case CMD_PUSH:
        stack_push(stack, instr.value);
        break;
    case CMD_ADD:
    {
        int a = stack_pop(stack);
        int b = stack_pop(stack);
        stack_push(stack, b + a);
        break;
    }
    case CMD_SUB:
    {
        int a = stack_pop(stack);
        int b = stack_pop(stack);
        stack_push(stack, b - a);
        break;
    }
    case CMD_MUL:
    {
        int a = stack_pop(stack);
        int b = stack_pop(stack);
        stack_push(stack, b * a);
        break;
    }
    case CMD_DIV:
    {
        int a = stack_pop(stack);
        int b = stack_pop(stack);
        stack_push(stack, b / a);
        break;
    }
    case CMD_PRINT:
        fprintf(stdout, "%d\n", stack_pop(stack));
        break;
    default:
        fprintf(stderr, "Invalid instruction command.\n");
        break;
    }
}