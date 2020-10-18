#ifndef VM_CODE_H
#define VM_CODE_H

#include <stdint.h>
#include "../vm_constant_pool.h"

/**
 * @brief
 */
typedef struct vm_exception_table
{
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
} vm_exception_table_t;

/**
 * @brief
 */
typedef struct vm_code
{
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t max_stack;
    uint16_t max_local;

    uint32_t code_length;
    uint8_t *code;

    uint16_t exception_table_length;
    vm_exception_table_t *exception_table;

    uint16_t attributes_count;
    vm_attribute_info_t *attributes;
} vm_code_t;

#endif /* VM_CODE_H */
