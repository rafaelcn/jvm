#include <stdio.h>

#include "vm_frame.h"

void push_into_stack(vm_stack_t **stack, vm_stack_t **new_frame) {
    // the new_frame points towards the former top_frame
    (*new_frame)->next_frame = *stack;
    // the new_frame is the new top_frame
    *stack = *new_frame;
}

void push_into_ostack(vm_ostack_t **stack, vm_ostack_t **new_frame) {
    // the new_frame points towards the former top_frame
    (*new_frame)->next_frame = *stack;
    // the new_frame is the new top_frame
    *stack = *new_frame;
}

vm_stack_t * pop_from_stack(vm_stack_t **stack) {
    // temporarily holds the former top_frame
    vm_stack_t *popped_frame = *stack;
    // a new top_frame is assigned to the stack
    *stack = popped_frame->next_frame;
    // the popped_frame points to NULL
    popped_frame->next_frame = NULL;

    return popped_frame;
}

vm_ostack_t * pop_from_ostack(vm_ostack_t **stack) {
    // temporarily holds the former top_frame
    vm_ostack_t *popped_frame = *stack;
    // a new top_frame is assigned to the stack
    *stack = popped_frame->next_frame;
    // the popped_frame points to NULL
    popped_frame->next_frame = NULL;

    return popped_frame;
}
