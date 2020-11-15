#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <stdint.h>

#include "vm_constant_pool.h"

typedef struct vm_ostack vm_ostack_t;
typedef struct vm_stack vm_stack_t;

enum local_variables_enum {
    _short,
    _int,
    _long,
    _float,
    _double,
    _char,
    _string,
    _byte_or_bool,
    _reference,
    _returnAddress
};

/**
 * @brief The value and type of the local_variables of the current STACK.
 * Also used to indicate the OperandStack operand value and type.
 */
typedef struct vm_local_variables {
    int type;
    union value {
        short _short;
        int _int;
        long _long;
        float _float;
        double _double;
        char _char;
        char *_string;
        uint8_t _byte_or_bool;
        void *_reference;
        uint32_t _returnAddress;
    } value;
} vm_local_variables_t;

/**
 * @brief A frame of the OperandStack;
 */
struct vm_ostack {
    vm_local_variables_t operand;
    vm_ostack_t *next_frame;
};

/**
 * @brief A frame of the Stack.
 */
struct vm_stack {
    char *StringBuilder;

    uint32_t pc;

    vm_local_variables_t *local_variables;
    vm_ostack_t *operand_stack;
    vm_cp_info_t *constant_pool;
    vm_stack_t *next_frame;
};

/**
 * @brief Pushes a stack_frame into the JVM Stack.
 * @param stack A pointer to the JVM Stack.
 * @param new_frame A pointer to the a new frame.
 */
void push_into_stack(vm_stack_t **stack, vm_stack_t **new_frame);

/**
 * @brief Pops the frame at the top of the JVM Stack.
 * @param stack A pointer to the JVM Stack.
 * @returns A pointer to the popped frame.
 */
vm_stack_t * pop_from_stack(vm_stack_t **stack);

/**
 * @brief Pushes a operand_stack_frame into the Operands Stack.
 * @param stack A pointer to the Operands Stack.
 * @param new_frame A pointer to the a new frame.
 */
void push_into_ostack(vm_ostack_t **stack, vm_ostack_t **new_frame);

/**
 * @brief Pops the frame at the top of the Operands Stack.
 * @param stack A pointer to the Operands Stack.
 * @returns A pointer to the popped frame.
 */
vm_ostack_t * pop_from_ostack(vm_ostack_t **stack);

#endif /* VM_FRAME_H */
