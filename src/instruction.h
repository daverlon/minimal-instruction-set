#pragma once

enum command_type
{
    CMD_INVALID = -1,

    // part 1
    CMD_PUSH,
    CMD_ADD,
    CMD_SUB,
    CMD_MUL,
    CMD_DIV,
    CMD_PRINT,

    // part 2
    CMD_DUP,
    CMD_SWAP,
    CMD_NEG,
    CMD_MOD,
    CMD_POP,
};

typedef struct
{
    enum command_type cmd;
    int value; // only used for PUSH
} instruction_t;