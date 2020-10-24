#ifndef VM_TYPE_PARAMETER_BOUND_TARGET_H
#define VM_TYPE_PARAMETER_BOUND_TARGET_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_type_parameter_bound_target {
    uint8_t type_parameter_index;
    uint8_t bound_index;
} vm_type_parameter_bound_target_t;

#endif /* VM_TYPE_PARAMETER_BOUND_TARGET_H */
