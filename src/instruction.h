#pragma once

#include "stdbool.h"

#define COMMAND_LIST(X) \
    X(PUSH)  \
    X(ADD)   \
    X(SUB)   \
    X(MUL)   \
    X(DIV)   \
    X(PRINT) \
    X(DUP)   \
    X(SWAP)  \
    X(NEG)   \
    X(MOD)   \
    X(POP)   \
    X(DEClARE_LABEL)   \
    X(JMP)   \
    X(JZ)    \
    X(JNZ)   \
    X(CALL)  \
    X(RET)   \
    X(HALT)

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

typedef struct
{
    char* file_name;
    size_t file_line;

    enum command_type cmd;
    int value;
    char *symbol_name;
} instruction_t;

enum token_type
{
    TOKEN_INVALID = -1,
    TOKEN_COMMAND,
    TOKEN_NUMBER,

    TOKEN_LABEL,
    TOKEN_SYMBOL
};