#ifndef VM_CONSTANT_VALUE_H
#define VM_CONSTANT_VALUE_H

#include <stdint.h>

/**
 * @brief A constant_value structure.
 */
typedef struct vm_constant_value {
    uint16_t constantvalue_index;
} vm_constant_value_t;

#endif /* VM_CONSTANT_VALUE_H */
