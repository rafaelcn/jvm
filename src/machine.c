#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "machine.h"

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
 * @brief Pushes a stack_frame into the JVM Stack.
 * @param stack A pointer to the JVM Stack.
 * @param new_frame A pointer to the a new frame.
 * @returns Nothing.
 */
void push_into_stack(vm_stack_t *stack, vm_stack_frame_t *new_frame) {
    // the new_frame points towards the former top_frame
    new_frame->next_frame = stack->top_frame;
    // the new_frame is the new top_frame
    stack->top_frame = new_frame;
}

/**
 * @brief Pushes a operand_stack_frame into the Operands Stack.
 * @param stack A pointer to the Operands Stack.
 * @param new_frame A pointer to the a new frame.
 * @returns Nothing.
 */
void push_into_stack(vm_operand_stack_t *stack, vm_operand_stack_frame_t *new_frame) {
    // the new_frame points towards the former top_frame
    new_frame->next_frame = stack->top_frame;
    // the new_frame is the new top_frame
    stack->top_frame = new_frame;
}

/**
 * @brief Pops the frame at the top of the JVM Stack.
 * @param stack A pointer to the JVM Stack.
 * @returns A pointer to the popped frame.
 */
vm_stack_frame_t * pop_from_stack(vm_stack_t *stack) {
    // temporarily holds the former top_frame
    vm_stack_frame_t *popped_frame = stack->top_frame;
    // a new top_frame is assigned to the stack
    stack->top_frame = popped_frame->next_frame;
    // the popped_frame points to NULL
    popped_frame->next_frame = NULL;
    return popped_frame;
}

/**
 * @brief Pops the frame at the top of the Operands Stack.
 * @param stack A pointer to the Operands Stack.
 * @returns A pointer to the popped frame.
 */
vm_operand_stack_frame_t * pop_from_stack(vm_operand_stack_t *stack) {
    // temporarily holds the former top_frame
    vm_operand_stack_frame_t *popped_frame = stack->top_frame;
    // a new top_frame is assigned to the stack
    stack->top_frame = popped_frame->next_frame;
    // the popped_frame points to NULL
    popped_frame->next_frame = NULL;
    return popped_frame;
}
