#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "program.h"
#include "vm.h"
#include "parser.h"
#include "interpreter.h"

static FILE *f = NULL;
static char *line = NULL;
static program_t prog = {0};
static vm_t vm = {0};

static void cleanup(void)
{
    program_clear(&prog);
    stack_clear(&vm.stack);
    if (f != NULL) fclose(f);
    if (line != NULL) free(line);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file.mis>\n", argv[0]);
        return 1;
    }

    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open file.\n");
        return 1;
    }

    atexit(cleanup);
    
    program_init(&prog);
    stack_init(&vm.stack);
    const char *delim = " ;,\t\n";
    size_t size = 0;

    while (getline(&line, &size, f) != EOF)
    {
        char *comment = strchr(line, ';');
        if (comment != NULL)
            *comment = '\0';
        if (line[0] == ';' || line[0] == '\n')
            continue;
        char *tok = strtok(line, delim);
        while (tok != NULL)
        {
            for (int c = 0; tok[c] != '\0'; c++)
                tok[c] = toupper(tok[c]);
            instruction_t instr;
            bool ready = parse_token(tok, &instr);
            if (ready)
                program_add_instruction(&prog, instr);
            // fprintf(stdout, "%s\n", tok);
            tok = strtok(NULL, delim);
        }
    }

    for (vm.pc = 0; vm.pc < prog.length; vm.pc++)
    {
        instruction_t *instr = &prog.instructions[vm.pc];
        execute_instruction(&vm, *instr);
    }

    exit(0);
}