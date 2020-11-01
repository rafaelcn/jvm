#ifndef VM_ENTRY_H
#define VM_ENTRY_H

#include <stdio.h>

/**
 * @brief The entry function of the java virtual machine. This method
 * initializes the java virtual machine internal structures
 * @param filename Is a filepath string pointing to a filename that contains a
 * valid .class file.
 */
int vm_init(const char *filename);

#endif /* VM_ENTRY_H */