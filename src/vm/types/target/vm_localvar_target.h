#ifndef VM_LOCALVAR_TARGET_H
#define VM_LOCALVAR_TARGET_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_localvar_target {
    uint16_t table_length;
    struct {
        uint16_t start_pc;
        uint16_t length;
        uint16_t index;
    } *table;
} vm_localvar_target_t;

#endif /* VM_LOCALVAR_TARGET_H */
