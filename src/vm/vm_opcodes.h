#ifndef VM_OPCODES_H
#define VM_OPCODES_H

#include <stdint.h>

#include "vm_frame.h"

/**
 * @brief 
 */
uint32_t vm_opcodes(uint8_t *bytes, uint32_t pc, vm_stack_t *STACK);

#endif /* VM_OPCODES_H */
