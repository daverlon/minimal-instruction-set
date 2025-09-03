#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vm.h"
#include "instruction.h"

#include "parser.h"
#include "interpreter.h"

static FILE *f = NULL;
static vm_t vm = {0};
static char *line = NULL;

static void cleanup(void)
{
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
            for (int c = 0; c < *tok; c++)
                tok[c] = toupper(tok[c]);
            instruction_t instr;
            bool ready = parse_token(tok, &instr);
            if (ready)
                execute_instruction(&vm, instr);
            // fprintf(stdout, "%s\n", tok);
            tok = strtok(NULL, delim);
        }
    }

    exit(0);
}