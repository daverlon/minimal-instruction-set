#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "interpreter.h"

enum token_type
{
    TOKEN_INVALID = -1,
    TOKEN_COMMAND,
    TOKEN_NUMBER
};

typedef struct
{
    const char *name;
    enum command_type type;
} command_map_t;

command_map_t commands[] = 
{
    {"PUSH", CMD_PUSH},
    {"ADD", CMD_ADD},
    {"SUB", CMD_SUB},
    {"MUL", CMD_MUL},
    {"DIV", CMD_DIV},
    {"PRINT", CMD_PRINT},

    {"DUP", CMD_DUP},
    {"SWAP", CMD_SWAP},
    {"NEG", CMD_NEG},
    {"MOD", CMD_MOD},
    {"POP", CMD_POP},
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
                fprintf(stderr, "Invalid command found: %s\n", token);
                exit(1);
            }
        
        }
    }
    case TOKEN_NUMBER:
    {
        for (int c = 0; c < *token; c++)
        {
            if (!isdigit(token[c]))
            {
                fprintf(stderr, "Expected digit found character: %c.\n", token[c]);
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