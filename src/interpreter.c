#include <stdio.h>
#include <stdlib.h>

#include "interpreter.h"

#include "vm.h"
#include "instruction.h"
#include "program.h"

void execute_instruction(vm_t *vm, const instruction_t instr, const symbol_table_t *sym_tab)
{
    my_stack_t *stack = &vm->stack;

    switch (instr.cmd)
    {
    case CMD_DEClARE_LABEL:
    {
        // fprintf(stdout, "Instruction declare label: %s\n", instr.symbol_name);
        break;
    }
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
        size_t len = stack->length;
        if (len <= 1)
        {
            fprintf(stderr, "Tried to swap when stack length = %zu\n", len);
            vm_abort(vm);
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
        if (stack->length <= 0)
        {
            fprintf(stderr, "Tried to neg when stack length = %zu\n", stack->length);
            vm_abort(vm);
        }
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
    case CMD_DUPRINT:
    {
        fprintf(stdout, "%d\n", stack_peak(stack));
        break;
    }

    // jumps
    case CMD_JMP:
    case CMD_JZ:
    case CMD_JNZ:
    // check for valid symbol
    {
        int address = symbol_table_find_symbol_address(sym_tab, instr.symbol_name);
        if (address < 0)
        {
            fprintf(stderr, "Failed to find symbol \"%s\" unknown.", instr.symbol_name);
            exit(1);
        }
        if (instr.cmd == CMD_JMP)
        {
            vm->pc = address;
            break;
        }
        else if (instr.cmd == CMD_JZ)
        {
            if (stack_pop(stack) == 0)
                vm->pc = address;
            break;
        }
        else if (instr.cmd == CMD_JNZ)
        {
            if (stack_pop(stack) != 0)
                vm->pc = address;
            break;
        }
    }

    default:
    {
        fprintf(stderr, "Invalid instruction command.\n");
        vm_abort(vm);
    }
    }
}