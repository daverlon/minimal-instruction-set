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
    {
        stack_push(stack, instr.value);
        break;
    }
    case CMD_DUP:
    {
        int dup_val = stack_peak(stack);
        stack_push(stack, dup_val);
        break;
    }
    case CMD_SWAP:
    {
        int len = stack->length;
        if (len <= 1)
        {
            fprintf(stderr, "Tried to swap when stack length = %d\n", len);
            exit(1);
        }
        int *a = &stack->data[len - 1];
        int *b = &stack->data[len - 2];
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
        break;
    } 
    case CMD_NEG:
    {
        int *a = &stack->data[stack->length - 1];
        *a *= -1;
        break;
    }
    case CMD_MOD:
    {
        int a = stack_pop(stack);
        int b = stack_pop(stack);
        stack_push(stack, b % a);
        break;
    }
    case CMD_POP:
    {
        stack_pop(stack);
        break;
    }
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
    {
        fprintf(stdout, "%d\n", stack_pop(stack));
        break;
    }
    default:
    {
        fprintf(stderr, "Invalid instruction command.\n");
        break;
    }
    }
}