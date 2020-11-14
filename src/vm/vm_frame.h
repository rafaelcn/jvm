#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <stdint.h>

#include "vm_constant_pool.h"

typedef struct vm_stack_frame vm_stack_frame_t;
typedef struct vm_operand_stack_frame vm_operand_stack_frame_t;
typedef struct vm_local_variable_item vm_local_variable_item_t;

/**
 * @brief A union with the types that will be used for local variables and operands stack.
 */
typedef union _values {
    int _int;
    float _float;
    double _double;
    char *_string;
} _values_t;

/**
 * @brief  A single local variable.
 * used to pass parameters on method invocation.
 */
struct vm_local_variable_item {
    _values_t value;
    vm_local_variable_item_t *next_item;
};

/**
 * @brief A list with the number of local variables and a pointer to the first one.
 */
typedef struct vm_local_variables_list {
    uint16_t local_variables_count;
    vm_local_variable_item_t *first_item;
} vm_local_variables_list_t;


/**
 * @brief A single frame of operands stack.
 */
struct vm_operand_stack_frame {
    _values_t value;
    vm_operand_stack_frame_t *next_frame;
} ;

/**
 * @brief A struct to count the number of frames and points to the top_frame.
 */
typedef struct vm_operand_stack {
    uint16_t frames_count;
    vm_operand_stack_frame_t *top_frame;
} vm_operand_stack_t;

/**
 * @brief The JVM supplies instructions to load constants or values from local variables or fields into the operand stack.
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
 */
void push_into_stack(vm_stack_t *stack, vm_stack_frame_t *new_frame);


/**
 * @brief Pops the frame at the top of the JVM Stack.
 * @param stack A pointer to the JVM Stack.
 * @returns A pointer to the popped frame.
 */
vm_stack_frame_t * pop_from_stack(vm_stack_t *stack);


/**
 * @brief Pushes a operand_stack_frame into the Operands Stack.
 * @param stack A pointer to the Operands Stack.
 * @param new_frame A pointer to the a new frame.
 */
void push_into_ostack(vm_operand_stack_t *stack, vm_operand_stack_frame_t *new_frame);


/**
 * @brief Pops the frame at the top of the Operands Stack.
 * @param stack A pointer to the Operands Stack.
 * @returns A pointer to the popped frame.
 */
vm_operand_stack_frame_t * pop_from_ostack(vm_operand_stack_t *stack);

#endif /* VM_FRAME_H */
