#ifndef VM_OPCODES_H
#define VM_OPCODES_H

#include <stdint.h>

#include "vm_frame.h"

/**
 * @brief The JVM instructions operations.
 * @param code the code of the instruction.
 * @param pc The previous PC position.
 * @param STACK An operands stack.
 * @returns The actual PC position.
 */
uint32_t vm_opcodes(uint8_t *code, uint32_t pc, vm_stack_t *STACK);

#endif /* VM_OPCODES_H */
