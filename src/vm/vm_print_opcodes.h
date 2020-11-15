#ifndef VM_PRINT_OPCODES_H
#define VM_PRINT_OPCODES_H

#include <stdint.h>

#include "vm_constant_pool.h"

/**
 * @brief A function that converts a OpCode into a JVM Mnemonic.
 * @param code The code field of a Code Attribute of Method.
 * @param pc The PC of the current instruction of the method.
 * @returns Returns the PC of the next instruction.
 */
uint32_t vm_print_opcodes_helper(uint8_t *code, uint32_t pc);

/**
 * @brief A function that prints the mnemonics associated with the OpCodes
 * of a the main method.
 * @param class_file A vm_class_file_t structure with a main method.
 */
void vm_print_opcodes(vm_class_file_t class_file);

#endif /* VM_PRINT_OPCODES_H */
