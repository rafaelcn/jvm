#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <stdint.h>

#include "vm_constant_pool.h"

typedef struct vm_stack_frame vm_stack_frame_t;
typedef struct vm_operand_stack_frame vm_operand_stack_frame_t;
typedef struct vm_local_variable_item vm_local_variable_item_t;

/**
 * @brief
 */
typedef union _values {
    int _int;
    float _float;
    char *_string;
} _values_t;

/**
 * @brief
 */
struct vm_local_variable_item {
    _values_t value;
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
    _values_t value;
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

void push_into_stack(vm_stack_t *stack, vm_stack_frame_t *new_frame);
vm_stack_frame_t * pop_from_stack(vm_stack_t *stack);

void push_into_ostack(vm_operand_stack_t *stack, vm_operand_stack_frame_t *new_frame);
vm_operand_stack_frame_t * pop_from_ostack(vm_operand_stack_t *stack);

#endif /* VM_FRAME_H */
