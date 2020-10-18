#ifndef VM_SOURCE_FILE_H
#define VM_SOURCE_FILE_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_source_file {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t sourcefile_index;
} vm_source_file_t;

#endif /* VM_SOURCE_FILE_H */
