#ifndef VM_SIGNATURE_H
#define VM_SIGNATURE_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_signature {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t signature_index;
} vm_signature_t;

#endif /* VM_SIGNATURE_H */
