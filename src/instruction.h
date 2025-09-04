#pragma once

#include <stdio.h>
#include <stdbool.h>

#define COMMAND_LIST(X) \
    X(PUSH)  \
    X(ADD)   \
    X(SUB)   \
    X(MUL)   \
    X(DIV)   \
    X(INC)   \
    X(DEC)   \
    X(PRINT) \
    X(DUPRINT)  \
    X(DUP)   \
    X(PICK)  \
    X(SWAP)  \
    X(NEG)   \
    X(MOD)   \
    X(POP)   \
    X(DEClARE_LABEL)   \
    X(JMP)   \
    X(JZ)    \
    X(JNZ)   \
    X(JL)    \
    X(JG)    \
    X(CALL)  \
    X(RET)   \
    X(HALT)  \

enum command_type {
    CMD_INVALID = -1,
    #define ENUM_DEF(name) CMD_##name,
    COMMAND_LIST(ENUM_DEF)
    #undef ENUM_DEF
};

typedef struct
{
    const char *name;
    enum command_type type;
} command_map_t;

enum command_type command_get_type(const char *command);
const char *command_get_name(enum command_type cmd);

typedef struct
{
    char* file_name;
    size_t file_line;

    enum command_type cmd;
    int value;
    char *symbol_name;
} instruction_t;

// Define the list of tokens
#define TOKEN_LIST(X) \
    X(INVALID) \
    X(COMMAND) \
    X(NUMBER)  \
    X(LABEL)   \
    X(SYMBOL)

// Define the enum
enum token_type {
    #define ENUM_DEF(name) TOKEN_##name,
    TOKEN_LIST(ENUM_DEF)
    #undef ENUM_DEF
};

extern const char *token_names[];

bool is_reserved_keyword(const char* str);