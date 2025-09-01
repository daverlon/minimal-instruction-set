#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

command_map_t commands[] = {
    {"PUSH", CMD_PUSH},
    {"ADD", CMD_ADD},
    {"SUB", CMD_SUB},
    {"MUL", CMD_MUL},
    {"DIV", CMD_DIV},
    {"PRINT", CMD_PRINT}};

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

static enum token_type expected_token = TOKEN_COMMAND;
bool parse_token(const char *token, instruction_t *out_instr)
{
    switch (expected_token)
    {
    case TOKEN_COMMAND:
    {
        enum command_type cmd = get_command_type(token);
        if (cmd == CMD_INVALID)
        {
            fprintf(stderr, "Invalid command found: %s\n", token);
            exit(1);
        }
        else if (cmd == CMD_PUSH)
        {
            out_instr->cmd = cmd;
            expected_token = TOKEN_NUMBER;
            return false;
        }
        else
        {
            out_instr->cmd = cmd;
            out_instr->value = 0;
            return true;
        }
    }
    case TOKEN_NUMBER:
    {
        out_instr->value = atoi(token);
        expected_token = TOKEN_COMMAND;
        return true;
    }
    default:
    {
        fprintf(stderr, "Invalid token found.\n");
        return false;
    }
    }
}