#pragma once

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
    X(POP)

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
} instruction_t;

enum token_type
{
    TOKEN_INVALID = -1,
    TOKEN_COMMAND,
    TOKEN_NUMBER
};