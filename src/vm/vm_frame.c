#include "vm_frame.h"

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
    // the frames_count is increased
    stack->frames_count += 1;

    return;
}

/**
 * @brief Pushes a operand_stack_frame into the Operands Stack.
 * @param stack A pointer to the Operands Stack.
 * @param new_frame A pointer to the a new frame.
 * @returns Nothing.
 */
void push_into_ostack(vm_operand_stack_t *stack, vm_operand_stack_frame_t *new_frame) {
    // the new_frame points towards the former top_frame
    new_frame->next_frame = stack->top_frame;
    // the new_frame is the new top_frame
    stack->top_frame = new_frame;
    // the frames_count is increased
    stack->frames_count += 1;

    return;
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
    // the frames_count is decreased
    stack->frames_count -= 1;
    // the popped_frame points to NULL
    popped_frame->next_frame = NULL;

    return popped_frame;
}

/**
 * @brief Pops the frame at the top of the Operands Stack.
 * @param stack A pointer to the Operands Stack.
 * @returns A pointer to the popped frame.
 */
vm_operand_stack_frame_t * pop_from_ostack(vm_operand_stack_t *stack) {
    // temporarily holds the former top_frame
    vm_operand_stack_frame_t *popped_frame = stack->top_frame;
    // a new top_frame is assigned to the stack
    stack->top_frame = popped_frame->next_frame;
    // the frames_count is increased
    stack->frames_count -= 1;
    // the popped_frame points to NULL
    popped_frame->next_frame = NULL;

    return popped_frame;
}
