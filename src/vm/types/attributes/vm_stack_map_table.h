#ifndef VM_STACK_MAP_TABLE_H
#define VM_STACK_MAP_TABLE_H

#include <stdint.h>

#include "vm_stack_map_frame.h"

/**
 * @brief
 */
typedef struct vm_stack_map_table {
    uint16_t number_of_entries;
    vm_stack_map_frame_t *entries;
} vm_stack_map_table_t;

#endif /* VM_STACK_MAP_TABLE_H */
