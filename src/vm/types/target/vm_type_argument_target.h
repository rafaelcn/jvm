#ifndef VM_TYPE_ARGUMENT_TARGET_H
#define VM_TYPE_ARGUMENT_TARGET_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_type_argument_target {
    uint16_t offset;
    uint8_t type_argument_index;
} vm_type_argument_target_t;

#endif /* VM_TYPE_ARGUMENT_TARGET_H */
