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
 * @brief
 * @param file
 */
void vm_inform(file_t *file);

/**
 * @brief
 * @param file
 */
const char * vm_execute(file_t *file);

#endif /* VM_ENTRY_H */