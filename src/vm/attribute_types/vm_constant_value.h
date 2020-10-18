#ifndef VM_CONSTANT_VALUE_H
#define VM_CONSTANT_VALUE_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_constant_value
{
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t constantvalue_index;
} vm_constant_value_t;

#endif /* VM_CONSTANT_VALUE_H */
