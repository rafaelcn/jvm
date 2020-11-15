#ifndef VM_LINE_NUMBER_TABLE_H
#define VM_LINE_NUMBER_TABLE_H

#include <stdint.h>

/**
 * @brief A line_number_table entry structure.
 */
typedef struct vm_line_number {
    uint16_t start_pc;
    uint16_t line_number;
} vm_line_number_t;

/**
 * @brief A line_number_table structure.
 */
typedef struct vm_line_number_table {
    uint16_t line_number_table_length;
    vm_line_number_t *line_number_table;
} vm_line_number_table_t;

#endif /* VM_LINE_NUMBER_TABLE_H */
