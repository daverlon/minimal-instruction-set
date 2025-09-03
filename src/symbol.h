#pragma once

#include <stdio.h>

#include "program.h"

typedef struct {
    const char *name; 
    size_t address;
} symbol_t;

typedef struct {
    symbol_t *symbols;
    size_t length;
} symbol_table_t;

void symbol_table_clear(symbol_table_t *symbol_table);
void symbol_table_add_symbol(symbol_table_t *symbol_table, symbol_t symbol);