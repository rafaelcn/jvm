#ifndef VM_LOCALVAR_TARGET_H
#define VM_LOCALVAR_TARGET_H

#include <stdint.h>

/**
 * @brief A vm_localvar_table structure.
 */
typedef struct vm_localvar_table {
        uint16_t start_pc;
        uint16_t length;
        uint16_t index;
    } vm_localvar_table_t;

/**
 * @brief A localvar_target structure.
 */
typedef struct vm_localvar_target {
    uint16_t table_length;
    vm_localvar_table_t *table;
} vm_localvar_target_t;

#endif /* VM_LOCALVAR_TARGET_H */
