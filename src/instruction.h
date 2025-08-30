#pragma once

enum command_type {
    CMD_INVALID = -1,
    CMD_PUSH,
    CMD_ADD,
    CMD_SUB,
    CMD_MUL,
    CMD_DIV,
    CMD_PRINT
};

struct instruction {
    enum command_type cmd;
    int value; // only used for PUSH
};