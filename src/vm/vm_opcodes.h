#ifndef VM_OPCODES_H
#define VM_OPCODES_H

#include <stdint.h>

#include "../machine.h"

typedef struct vm_stack_frame vm_stack_frame_t;
typedef struct vm_operand_stack_frame vm_operand_stack_frame_t;
typedef struct vm_local_variable_item vm_local_variable_item_t;

/**
 * @brief
 */
struct vm_local_variable_item {
    // some form of value here
    vm_local_variable_item_t *next_item;
};

/**
 * @brief
 */
typedef struct vm_local_variables_list {
    uint16_t local_variables_count;
    vm_local_variable_item_t *first_item;
} vm_local_variables_list_t;

/**
 * @brief
 */
struct vm_operand_stack_frame {
    // some form of value here
    vm_operand_stack_frame_t *next_frame;
} ;

/**
 * @brief
 */
typedef struct vm_operand_stack {
    uint16_t frames_count;
    vm_operand_stack_frame_t *top_frame;
} vm_operand_stack_t;

/**
 * @brief
 */
struct vm_stack_frame {
    vm_local_variables_list_t *local_variables_list;
    vm_operand_stack_t *operand_stack;
    vm_cp_info_t *constant_pool;
    vm_stack_frame_t *next_frame;
} ;

/**
 * @brief
 */
typedef struct vm_stack {
    uint16_t frames_count;
    vm_stack_frame_t *top_frame;
} vm_stack_t;

/**
 * @brief
 */
uint32_t vm_opcodes(uint8_t *bytes, uint32_t pc, vm_stack_t *STACK);

#endif /* VM_OPCODES_H */
