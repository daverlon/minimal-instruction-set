#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "instruction.h"
#include "interpreter.h"

bool parse_token(const char *token, instruction_t *out_instr)
{
    static enum token_type expected_token = TOKEN_LABEL;

    switch (expected_token)
    {
    case TOKEN_LABEL:
    {
        if (token[0] == ':')
        {
            size_t tklen = sizeof(token);
            for (size_t c = 1; c < tklen; c++)
            {
                if (token[c] == '\0') break;
                if (!isalnum(token[c]) && token[c] != '_')
                {
                    fprintf(stderr, "Expected alphanumerical characters and underscores only for label \"%s\" in line %zu, file %s\n", token+1, out_instr->file_line, out_instr->file_name);
                    fprintf(stderr, "Found invalid character '%c'\n", token[c]);
                    exit(1);
                }
            }
            // fprintf(stdout, "Found label: %s\n", token+1);
            out_instr->cmd = CMD_DEClARE_LABEL;
            size_t name_len = strlen(token + 1);
            if (out_instr->symbol_name != NULL) free(out_instr->symbol_name);
            out_instr->symbol_name = strdup(token+1);
            expected_token = TOKEN_COMMAND;
            return true;
        }
        else
        {
            // maybe this is a command?
            expected_token = TOKEN_COMMAND;
        }
    }
    case TOKEN_COMMAND:
    {
        enum command_type cmd = command_get_type(token);
        
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
            case CMD_DUPRINT:

            case CMD_DUP:
            case CMD_SWAP:
            case CMD_NEG:
            case CMD_MOD:
            case CMD_POP:
            {
                out_instr->cmd = cmd;
                out_instr->value = 0;
                expected_token = TOKEN_LABEL;
                return true;
            }

            case CMD_JMP:
            case CMD_JZ:
            case CMD_JNZ:
            {
                out_instr->cmd = cmd;
                out_instr->value = 0;
                expected_token = TOKEN_SYMBOL;
                return false;
            }

            case CMD_INVALID:
            default:
            {
                fprintf(stderr, "Invalid command found: \"%s\" at line %zu in file %s\n", token, out_instr->file_line, out_instr->file_name);
                fprintf(stderr, "Expected token: %s\n", token_names[expected_token]);
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
        expected_token = TOKEN_LABEL;
        return true;
    }
    // symbol from a jmp command
    case TOKEN_SYMBOL:
    {
        out_instr->symbol_name = strdup(token);
        expected_token = TOKEN_LABEL;
        return true;
    }
    default:
    {
        fprintf(stderr, "Invalid token found.\n");
        exit(1);
    }
    }
}