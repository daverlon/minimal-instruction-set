#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "instruction.h"
#include "interpreter.h"

enum token_type
{
    TOKEN_INVALID = -1,
    TOKEN_COMMAND,
    TOKEN_NUMBER
};

struct command_map
{
    const char *name;
    enum command_type type;
};

struct command_map commands[] = {
    {"PUSH", CMD_PUSH},
    {"ADD", CMD_ADD},
    {"SUB", CMD_SUB},
    {"MUL", CMD_MUL},
    {"DIV", CMD_DIV},
    {"PRINT", CMD_PRINT}};

enum command_type get_command_type(const char *command)
{
    int n_commands = sizeof(commands) / sizeof(struct command_map);
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
static struct instruction instr = {};

void parse_token(my_stack_t *stack, const char *token)
{
    switch (expected_token)
    {
    case TOKEN_COMMAND:
    {
        enum command_type cmd = get_command_type(token);
        if (cmd == CMD_INVALID)
        {
            fprintf(stderr, "Invalid command found: %s\n", token);
            stack_clear(stack);
            exit(1);
            break;
        }
        else if (cmd == CMD_PUSH)
        {
            instr.cmd = cmd;
            expected_token = TOKEN_NUMBER;
        }
        else
        {
            instr.cmd = cmd;
            instr.value = 0;
            execute_instruction(stack, instr);
        }
        break;
    }
    case TOKEN_NUMBER:
        instr.value = atoi(token);
        execute_instruction(stack, instr);
        expected_token = TOKEN_COMMAND;
        break;
    default:
        fprintf(stderr, "Invalid token found.\n");
    }
}