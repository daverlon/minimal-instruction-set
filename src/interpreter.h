#pragma once

#include "instruction.h"
#include "vm.h"

void execute_instruction(vm_t *vm, const instruction_t instr);