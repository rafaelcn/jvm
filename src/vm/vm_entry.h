#ifndef VM_ENTRY_H
#define VM_ENTRY_H

#include <stdio.h>

#include "vm_file.h"
#include "vm_opcodes.h"
#include "vm_constant_pool.h"


/**
 * @brief The entry function of the java virtual machine. This method
 * initializes the java virtual machine internal structures
 * @param filename Is a filepath string pointing to a filename that contains a
 * valid .class file.
 * @param file
 */
int vm_init(const char *filename, file_t *file);

/**
 * @brief This function is used only to read the classfile and show information
 * about the constant pool.
 * @param file A pointer to a file_t structure which holds data about the .class
 * file.
 */
void vm_inform(file_t *file);

/**
 * @brief This function is used to execute code from a .class file.
 * @param file A pointer to a file_t structure which holds data about the .class
 * file.
 */
const char * vm_execute(file_t *file);

#endif /* VM_ENTRY_H */