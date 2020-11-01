#ifndef VM_NAME_AND_TYPE_H
#define VM_NAME_AND_TYPE_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_name_and_type_t
{
    uint16_t name_index;
    uint16_t descriptor_index;
} vm_name_and_type_t;

#endif /* VM_NAME_AND_TYPE_H */