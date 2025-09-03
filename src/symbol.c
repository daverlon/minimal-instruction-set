#include "symbol.h"

#include "stdlib.h"

void symbol_table_clear(symbol_table_t *symbol_table)
{
    if (symbol_table->symbols != NULL) free(symbol_table->symbols);
    symbol_table->length = 0;
}

void symbol_table_add_symbol(symbol_table_t *symbol_table, symbol_t symbol)
{
    if (symbol_table->length <= 0)
    {
        symbol_table->symbols = malloc(sizeof(symbol_t));
        symbol_table->symbols[0] = symbol;
        symbol_table->length = 1;
    }
    else if (symbol_table->symbols)
    {
        symbol_table->symbols = realloc(symbol_table->symbols, sizeof(symbol_t) * (symbol_table->length + 1));
        symbol_table->symbols[symbol_table->length] = symbol;
        symbol_table->length++;
    }
}

void symbol_table_resolve_symbols(symbol_table_t *symbol_table, program_t *program)
{
    size_t n = program->length - 1;
    for (size_t i = 0; i < n; i++)
    {
        instruction_t *instr = &program->instructions[i];
        if (instr->cmd == CMD_DEClARE_LABEL)
        {
            // symbol_t sym = {instr-}
            // symbol_table_add_symbol(symbol_table, symbol)
        }
    }
}