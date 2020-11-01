#ifndef VM_INVOKE_DYNAMIC_H
#define VM_INVOKE_DYNAMIC_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_invoke_dynamic {
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
} vm_invoke_dynamic_t;

#endif /* VM_INVOKE_DYNAMIC_H */
