#ifndef MACHINE_H
#define MACHINE_H

#include "vm/vm_constant_pool.h"
#include "vm/vm_opcodes.h"

void vm_inform(file_t *file);
const char * vm_execute(file_t *file);

#endif /* MACHINE_H */
