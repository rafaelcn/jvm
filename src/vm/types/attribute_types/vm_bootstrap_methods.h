#ifndef VM_BOOTSTRAP_METHODS_H
#define VM_BOOTSTRAP_METHODS_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_bootstrap_methods {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t num_bootstrap_methods;
    struct {
        uint16_t bootstrap_method_ref;
        uint16_t num_bootstrap_arguments;
        uint16_t *bootstrap_arguments;
    } *bootstrap_methods;
} vm_bootstrap_methods_t;

#endif /* VM_BOOTSTRAP_METHODS_H */
