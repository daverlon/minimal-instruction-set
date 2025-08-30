#include <stdio.h>

#include "stack.h"
#include "instruction.h"

void execute_instruction(struct instruction instr) {
    switch (instr.cmd) {
    case CMD_PUSH:
        stack_push(instr.value);
        break;
    case CMD_ADD: {
        stack_push(stack_pop() + stack_pop());
        break;
    }
    case CMD_SUB: {
        int a = stack_pop();
        int b = stack_pop();
        stack_push(b - a);
        break;
    }
    case CMD_MUL: {
        stack_push(stack_pop() * stack_pop());
        break;
    }
    case CMD_DIV: {
        int a = stack_pop();
        int b = stack_pop();
        stack_push(b / a);
        break;
    }
    case CMD_PRINT:
        fprintf(stdout, "%d\n", stack_pop());
        break;
    default:
        fprintf(stderr, "Invalid instruction command.\n");
        break;
    }
}