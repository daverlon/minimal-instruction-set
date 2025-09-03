#include "program.h"

#include <stdlib.h>

#define DEFAULT_SIZE 8

void program_init(program_t *prog)
{
    prog->instructions = malloc(sizeof(instruction_t) * DEFAULT_SIZE);
    prog->capacity = DEFAULT_SIZE; 
    prog->length = 0;
}

void program_add_instruction(program_t *prog, instruction_t instr)
{
    if (prog->capacity <= 0)
    {
        prog->instructions = malloc(sizeof(instruction_t) * DEFAULT_SIZE);
        prog->capacity = DEFAULT_SIZE;
    }
    if (prog->length >= prog->capacity)
    {
        prog->instructions = realloc(prog->instructions, sizeof(instruction_t) * prog->capacity * 2);
        prog->capacity *= 2;
    }

    prog->instructions[prog->length] = instr;
    prog->length++;
}

void program_clear(program_t *prog)
{
    size_t n = prog->length;
    for (int i = 0; i < n; i++)
    {
        if (prog->instructions[i].symbol_name != NULL)
        {
            fprintf(stdout, "Destroying %s\n", prog->instructions[i].symbol_name);
            free(prog->instructions[i].symbol_name);
        }
    }
    if (prog->instructions != NULL) free(prog->instructions);
    
    prog->capacity = 0;
    prog->length = 0;
}