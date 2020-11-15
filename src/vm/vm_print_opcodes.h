#ifndef VM_PRINT_OPCODES_H
#define VM_PRINT_OPCODES_H

#include <stdint.h>

#include "vm_constant_pool.h"

uint32_t vm_print_opcodes_helper(uint8_t *code, uint32_t pc);
void vm_print_opcodes(vm_class_file_t class_file);

#endif /* VM_PRINT_OPCODES_H */
