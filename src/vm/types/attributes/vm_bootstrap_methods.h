#ifndef VM_BOOTSTRAP_METHODS_H
#define VM_BOOTSTRAP_METHODS_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_bootstrap_methods_table{
    uint16_t bootstrap_method_ref;
    uint16_t num_bootstrap_arguments;
    uint16_t *bootstrap_arguments;
} vm_bootstrap_methods_table_t;

/**
 * @brief
 */
typedef struct vm_bootstrap_methods {
    uint16_t num_bootstrap_methods;
    vm_bootstrap_methods_table_t *bootstrap_methods_table;
} vm_bootstrap_methods_t;

#endif /* VM_BOOTSTRAP_METHODS_H */
