#include "program.h"

#include <stdlib.h>

#define DEFAULT_SIZE 8

void program_init(program_t *prog)
{
    prog->instructions = malloc(sizeof(instruction_t) * DEFAULT_SIZE);
    prog->length = DEFAULT_SIZE; 
}

void program_add_instruction(program_t *prog, instruction_t instr)
{
    if (prog->capacity <= 0 || prog->instructions == NULL)
    {
        prog->instructions = malloc(sizeof(prog->instructions) * DEFAULT_SIZE);
        prog->length = DEFAULT_SIZE;
    }
    if (prog->length >= prog->capacity)
    {
        prog->instructions = realloc(prog->instructions, prog->capacity * 2);
        prog->capacity *= 2;
    }
}

void program_clear(program_t *prog)
{
    if (prog->instructions != NULL) free(prog->instructions);
}