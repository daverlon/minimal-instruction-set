#include "symbol.h"

#include "string.h"
#include "stdlib.h"

void symbol_table_clear(symbol_table_t *sym_tab)
{
    for (size_t i = 0; i < sym_tab->length; i++)
    {
        if (sym_tab->symbols[i].name != NULL) free(sym_tab->symbols[i].name);
    }
    if (sym_tab->symbols != NULL) free(sym_tab->symbols);
    sym_tab->length = 0;
}

void symbol_table_add_symbol(symbol_table_t *sym_tab, symbol_t symbol)
{
    if (sym_tab->length <= 0)
    {
        sym_tab->symbols = malloc(sizeof(symbol_t));
        sym_tab->symbols[0] = symbol;
        sym_tab->length = 1;
    }
    else if (sym_tab->symbols)
    {
        sym_tab->symbols = realloc(sym_tab->symbols, sizeof(symbol_t) * (sym_tab->length + 1));
        sym_tab->symbols[sym_tab->length] = symbol;
        sym_tab->length++;
    }
}

int symbol_table_find_symbol_address(const symbol_table_t *sym_tab, const char *symbol)
{
    ssize_t len = sym_tab->length;
    for (int i = 0; i < len; i++)
    {
        if (!strcmp(sym_tab->symbols[i].name, symbol))
        {
            int addressOut = sym_tab->symbols[i].address;
            return addressOut;
        }
    }
    return -1;
}