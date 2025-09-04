#pragma once

#include <stdio.h>

#include "program.h"

typedef struct {
    char *name; 
    size_t address;
} symbol_t;

typedef struct {
    symbol_t *symbols;
    size_t length;
} symbol_table_t;

void symbol_table_clear(symbol_table_t *sym_tab);
void symbol_table_add_symbol(symbol_table_t *sym_tab, symbol_t symbol);

int symbol_table_find_symbol_address(const symbol_table_t *sym_tab, const char *symbol);