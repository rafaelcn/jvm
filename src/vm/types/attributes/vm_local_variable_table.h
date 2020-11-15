#ifndef VM_LOCAL_VARIABLE_TABLE_H
#define VM_LOCAL_VARIABLE_TABLE_H

#include <stdint.h>

/**
 * @brief A local_variable (attribute) structure.
 */
typedef struct vm_local_variable {
    uint16_t start_pc;
    uint16_t length;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t index;
} vm_local_variable_t;

/**
 * @brief A local_variable_table (attribute) structure.
 */
typedef struct vm_local_variable_table {
    uint16_t local_variable_table_length;
    vm_local_variable_t *local_variable_table;
} vm_local_variable_table_t;

#endif /* VM_LOCAL_VARIABLE_TABLE_H */
