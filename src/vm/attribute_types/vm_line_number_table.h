#ifndef VM_LINE_NUMBER_TABLE_H
#define VM_LINE_NUMBER_TABLE_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_line_number {
    uint16_t start_pc;
    uint16_t line_number;
} vm_line_number_t;

/**
 * @brief
 */
typedef struct vm_line_number_table {
    uint16_t attribute_name_index;
    uint32_t attribute_length;

    uint16_t line_number_table_length;
    vm_line_number_t *line_number_table;
} vm_line_number_table_t;

#endif /* VM_LINE_NUMBER_TABLE_H */
