#pragma once

#include <stdio.h>

#include "instruction.h"

typedef struct 
{
    instruction_t *instructions;
    size_t length;
    size_t capacity;
} program_t;

void program_init(program_t *prog);
void program_add_instruction(program_t *prog, instruction_t instr);
void program_delete_instruction(program_t *prog, int index);
void program_clear(program_t *prog);