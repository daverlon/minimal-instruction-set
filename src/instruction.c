#include "instruction.h"

#include <string.h>
#include <stdbool.h>

command_map_t commands[] = {
    #define MAP_DEF(name) { #name, CMD_##name },
    COMMAND_LIST(MAP_DEF)
    #undef MAP_DEF
};

enum command_type command_get_type(const char *command)
{
    int n_commands = sizeof(commands) / sizeof(command_map_t);
    for (int i = 0; i < n_commands; i++) {
        if (strcmp(command, commands[i].name) == 0)
            return commands[i].type;
    }
    return CMD_INVALID;
}

const char *command_get_name(enum command_type cmd)
{
    int n_commands = sizeof(commands) / sizeof(command_map_t);
    for (int i = 0; i < n_commands; i++) {
        if (commands[i].type == cmd)
            return commands[i].name;
    }
    return "INVALID";
}

const char *token_names[] = {
    #define STR_DEF(name) #name,
    TOKEN_LIST(STR_DEF)
    #undef STR_DEF
};

#define STR_DEF(name) #name,
const char *reserved_keywords[] = {
    // "START",
    COMMAND_LIST(STR_DEF)
};

static const size_t n_reserved_keywords = sizeof(reserved_keywords) / sizeof(reserved_keywords[0]);

bool is_reserved_keyword(const char* str)
{
    for (int i = 0; i < n_reserved_keywords; i++)
    {
        if (!strcmp(str, reserved_keywords[i]))
            return true;
    }
    return false;
}