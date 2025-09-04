#include <stdio.h>
#include <stdlib.h>

#include "interpreter.h"

#include "vm.h"
#include "instruction.h"
#include "program.h"

static void print_runtime_error(instruction_t instr)
{
    fprintf(stderr, "Runtime error at line %zu, file %s\n", instr.file_line, instr.file_name);
}

void execute_instruction(vm_t *vm, const instruction_t instr, const symbol_table_t *sym_tab)
{
    my_stack_t *stack = &vm->data_stack;
    my_stack_t *call_stack = &vm->call_stack;

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
        int dup_val = 0;
        bool success = stack_peak(stack, &dup_val);
        if (!success)
        {
            print_runtime_error(instr);
            fprintf(stderr, "Runtime error at line %zu, file %s\n", instr.file_line, instr.file_name);
            exit(1);
        }
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
        int a = 0;
        int b = 0;
        bool success_a = stack_pop(stack, &a);
        bool success_b = stack_pop(stack, &b);
        if (!success_a || !success_b)
        {
            print_runtime_error(instr);
            exit(1);
        }
        stack_push(stack, b % a);
        break;
    }
    case CMD_POP:
    {
        int a = 0;
        bool success = stack_pop(stack, &a);
        if (!success)
        {
            print_runtime_error(instr);
            exit(1);
        }
        break;
    }
    case CMD_ADD:
    {
        int a = 0;
        int b = 0;
        bool success_a = stack_pop(stack, &a);
        bool success_b = stack_pop(stack, &b);
        if (!success_a || !success_b)
        {
            print_runtime_error(instr);
            exit(1);
        }
        stack_push(stack, b + a);
        break;
    }
    case CMD_SUB:
    {
        int a = 0;
        int b = 0;
        bool success_a = stack_pop(stack, &a);
        bool success_b = stack_pop(stack, &b);
        if (!success_a || !success_b)
        {
            print_runtime_error(instr);
            exit(1);
        }
        stack_push(stack, b - a);
        break;
    }
    case CMD_MUL:
    {
        int a = 0;
        int b = 0;
        bool success_a = stack_pop(stack, &a);
        bool success_b = stack_pop(stack, &b);
        if (!success_a || !success_b)
        {
            print_runtime_error(instr);
            exit(1);
        }
        stack_push(stack, b * a);
        break;
    }
    case CMD_DIV:
    {
        int a = 0;
        int b = 0;
        bool success_a = stack_pop(stack, &a);
        bool success_b = stack_pop(stack, &b);
        if (!success_a || !success_b)
        {
            print_runtime_error(instr);
            exit(1);
        }
        stack_push(stack, b / a);
        break;
    }
    case CMD_PRINT:
    {
        int a = 0;
        bool success = stack_pop(stack, &a);
        if (!success)
        {
            print_runtime_error(instr);
            exit(1);
        }
        fprintf(stdout, "%d\n", a);
        break;
    }
    case CMD_DUPRINT:
    {
        int dup_val = 0;
        bool success = stack_peak(stack, &dup_val);
        if (!success)
        {
            fprintf(stderr, "Runtime error at line %zu, file %s\n", instr.file_line, instr.file_name);
        }
        fprintf(stdout, "%d\n", dup_val);
        break;
    }

    // jumps
    case CMD_JMP:
    case CMD_JZ:
    case CMD_JNZ:

    case CMD_CALL:
    {
        int address = symbol_table_find_symbol_address(sym_tab, instr.symbol_name);
        if (address < 0)
        {
            fprintf(stderr, "Failed to find symbol \"%s\" unknown.\n", instr.symbol_name);
            exit(1);
        }
        if (instr.cmd == CMD_JMP)
        {
            vm->pc = address;
            break;
        }
        else if (instr.cmd == CMD_JZ)
        {
            int a = 0;
            bool success = stack_pop(stack, &a);
            if (!success)
            {
                print_runtime_error(instr);
                exit(1);
            }
            if (a == 0)
                vm->pc = address;
            break;
        }
        else if (instr.cmd == CMD_JNZ)
        {
            int a = 0;
            bool success = stack_pop(stack, &a);
            if (!success)
            {
                print_runtime_error(instr);
                exit(1);
            }
            if (a != 0)
                vm->pc = address;
            break;
        }
        else if (instr.cmd == CMD_CALL)
        {
            stack_push(call_stack, vm->pc + 1);
            vm->pc = address;
            break;
        }
    }
    case CMD_RET:
    {
        int a = 0;
        bool success = stack_pop(call_stack, &a);
        if (!success)
        {
            print_runtime_error(instr);
            exit(1);
        }
        vm->pc = a;
        break;
    }

    case CMD_HALT:
    {
        exit(0);
    }

    case CMD_PICK:
    {
        int a = 0;
        bool success = stack_pick(stack, instr.value, &a);
        if (!success)
        {
            print_runtime_error(instr);
            exit(1);
        }
        stack_push(stack, a);
        break;
    }

    default:
    {
        fprintf(stderr, "Invalid instruction command.\n");
        vm_abort(vm);
    }
    }
}