#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "instruction.h"
#include "interpreter.h"

command_map_t commands[] = {
    #define MAP_DEF(name) { #name, CMD_##name },
    COMMAND_LIST(MAP_DEF)
    #undef MAP_DEF
};

enum command_type get_command_type(const char *command)
{
    int n_commands = sizeof(commands) / sizeof(command_map_t);
    for (int i = 0; i < n_commands; i++)
    {
        if (!strcmp(command, commands[i].name))
        {
            return commands[i].type;
        }
    }
    return -1;
}

bool parse_token(const char *token, instruction_t *out_instr)
{
    static enum token_type expected_token = TOKEN_COMMAND;

    switch (expected_token)
    {
    case TOKEN_COMMAND:
    {
        enum command_type cmd = get_command_type(token);
        
        switch (cmd) 
        {
            case CMD_PUSH: 
            {
                out_instr->cmd = cmd;
                expected_token = TOKEN_NUMBER;
                return false;
            }

            case CMD_ADD:
            case CMD_SUB:
            case CMD_MUL:
            case CMD_DIV:
            case CMD_PRINT:

            case CMD_DUP:
            case CMD_SWAP:
            case CMD_NEG:
            case CMD_MOD:
            case CMD_POP:
            {
                out_instr->cmd = cmd;
                out_instr->value = 0;
                return true;
            }

            case CMD_INVALID:
            default:
            {
                fprintf(stderr, "Invalid command found: %s at line %zu in file %s\n", token, out_instr->file_line, out_instr->file_name);
                exit(1);
            }
        
        }
    }
    case TOKEN_NUMBER:
    {
        for (int c = 0; token[c] != '\0'; c++)
        {
            if (!isdigit(token[c]))
            {
                fprintf(stderr, "Expected digit found character: '%c'\n", token[c]);
                exit(1);
            }
        }
        out_instr->value = atoi(token);
        expected_token = TOKEN_COMMAND;
        return true;
    }
    default:
    {
        fprintf(stderr, "Invalid token found.\n");
        exit(1);
    }
    }
    exit(1);
}