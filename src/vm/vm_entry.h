#ifndef VM_ENTRY_H
#define VM_ENTRY_H

#include <stdio.h>

/**
 * @brief Represents a java .class file to be used when reading information from
 * the file.
 */
typedef struct file_t {
    // The name of the .class file
    const char* filename;
    // Pointer to the first byte read of the java .class file
    const char* data;
    // size of the java .class file in bytes
    size_t size;
    // Read bytes of the file. Used whenever you want to seek n bytes to the
    // beginning of the file.
    size_t read;
} file_t;

/**
 * @brief The entry function of the java virtual machine. This method
 * initializes the java virtual machine internal structures
 * @param filename Is a filepath string pointing to a filename that contains a
 * valid .class file.
 */
int vm_init(const char *filename);

#endif /* VM_ENTRY_H */