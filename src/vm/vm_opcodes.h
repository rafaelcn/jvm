#ifndef VM_OPCODES_H
#define VM_OPCODES_H

#include <stdint.h>

#include "vm_frame.h"

enum array_type_enum {
    T_BOOLEAN = 4,
    T_CHAR,
    T_FLOAT,
    T_DOUBLE,
    T_BYTE,
    T_SHORT,
    T_INT,
    T_LONG
};

/**
 * @brief
 */
void vm_opcodes(uint8_t *code, uint32_t *pc, vm_stack_t *STACK);

#endif /* VM_OPCODES_H */
