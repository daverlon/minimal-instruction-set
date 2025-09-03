#include <stdlib.h>

#include "vm.h"

void vm_abort(vm_t *vm)
{
    fprintf(stderr, "Interpreter abort at instruction %zu on line %zu in file %s\n", vm->pc, vm->file_line, vm->file_name);
    exit(1);
}