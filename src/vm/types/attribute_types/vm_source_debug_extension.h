#ifndef VM_SOURCE_DEBUG_EXTENSION_H
#define VM_SOURCE_DEBUG_EXTENSION_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_source_debug_extension {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint8_t *debug_extension;
} vm_source_debug_extension_t;

#endif /* VM_SOURCE_DEBUG_EXTENSION_H */
