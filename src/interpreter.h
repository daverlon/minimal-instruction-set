#pragma once

#include "instruction.h"
#include "vm.h"
#include "symbol.h"

void execute_instruction(vm_t *vm, const instruction_t instr, const symbol_table_t *sym_tab);