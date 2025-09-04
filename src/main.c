#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "program.h"
#include "vm.h"
#include "parser.h"
#include "interpreter.h"
#include "symbol.h"
#include "instruction.h"

static FILE *f = NULL;
static char *line = NULL;
static program_t prog = {0};
static vm_t vm = {0};
static symbol_table_t sym_tab = {0};

static void print_instruction_debug_msg(instruction_t instr)
{
    fprintf(stdout, "Add instruction { ");

    if (instr.cmd == CMD_DEClARE_LABEL || instr.cmd == CMD_JMP)
        fprintf(stdout, "%s : %s", command_get_name(instr.cmd), instr.symbol_name);
    else if (instr.cmd == CMD_PUSH)
        fprintf(stdout, "%s : %d", command_get_name(instr.cmd), instr.value);
    else
        fprintf(stdout, "%s", command_get_name(instr.cmd));

    fprintf(stdout, " }\n");
}

static void cleanup(void)
{
    symbol_table_clear(&sym_tab);
    program_clear(&prog);
    stack_clear(&vm.stack);
    if (vm.file_name != NULL) free(vm.file_name);
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

    vm.file_name = malloc(strlen(argv[1]) + 1);
    strcpy(vm.file_name, argv[1]);
    vm.file_line = 0;

    atexit(cleanup);
    
    program_init(&prog);
    stack_init(&vm.stack);
    const char *delim = " ;,\t\n";
    size_t size = 0;

    while (getline(&line, &size, f) != EOF)
    {
        vm.file_line++;
        char *comment = strchr(line, ';');
        if (comment != NULL)
            *comment = '\0';
        if (line[0] == ';' || line[0] == '\n')
            continue;
        char *tok = strtok(line, delim);
        instruction_t instr = {0};
        while (tok != NULL)
        {
            for (int c = 0; tok[c] != '\0'; c++)
                tok[c] = toupper(tok[c]);
            instr.file_name = vm.file_name;
            instr.file_line = vm.file_line;
            bool ready = parse_token(tok, &instr);
            if (ready)
            {
                // print_instruction_debug_msg(instr);
                program_add_instruction(&prog, instr);
                // if (instr.symbol_name != NULL) free(instr.symbol_name);
            }

            tok = strtok(NULL, delim);
        }
    }

    int address_main = 0;
    // resolve symbols first
    for (int i = 0; i < prog.length; i++)
    {
        instruction_t *instr = &prog.instructions[i];
        if (instr->cmd == CMD_DEClARE_LABEL)
        {
            symbol_t sym = {0};
            sym.name = strdup(instr->symbol_name);
            sym.address = i;
            symbol_table_add_symbol(&sym_tab, sym);

            if (!strcmp(sym.name, "main")) address_main = i;

            program_delete_instruction(&prog, i);
        }
    }

    // now run
    while (vm.pc < prog.length)
    {
        instruction_t *instr = &prog.instructions[vm.pc];
        int x = vm.pc;
        execute_instruction(&vm, *instr, &sym_tab);
        if (x == vm.pc) vm.pc++;
    }

    exit(0);
}