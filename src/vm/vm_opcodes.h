#ifndef VM_OPCODES_H
#define VM_OPCODES_H

#include <stdint.h>

#include "vm_frame.h"

/**
 * A 
 */
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
 * @brief A function that executes an opcode of the JVM.
 * @param code The code field of a Code Attribute of a Method.
 * @param pc The PC of the current instruction of the method.
 * @returns The PC of the next instruction.
 */
uint32_t vm_opcodes(uint8_t *code, uint32_t pc, vm_stack_t *STACK);

#endif /* VM_OPCODES_H */
