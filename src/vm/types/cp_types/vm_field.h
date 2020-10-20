#ifndef VM_FIELD_H
#define VM_FIELD_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_field_ref_t
{
    uint16_t class_index;
    uint16_t name_and_type_index;
} vm_field_ref_t;

#endif /* VM_FIELD_H */