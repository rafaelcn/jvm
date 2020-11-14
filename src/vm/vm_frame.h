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
    _reference
};

/**
 * @brief
 */
typedef struct vm_local_variables {
    int type;
    union {
        short _short;
        int _int;
        long _long;
        float _float;
        double _double;
        char _char;
        char *_string;
        uint8_t _byte_or_bool;
        void *_reference;
    } value;
} vm_local_variables_t;

/**
 * @brief
 */
struct vm_ostack {
    vm_local_variables_t operand;
    vm_ostack_t *next_frame;
};

/**
 * @brief
 */
struct vm_stack {
    char *StringBuilder;

    vm_local_variables_t *local_variables;
    vm_ostack_t *operand_stack;
    vm_cp_info_t *constant_pool;
    vm_stack_t *next_frame;
};

void push_into_stack(vm_stack_t **stack, vm_stack_t **new_frame);
vm_stack_t * pop_from_stack(vm_stack_t **stack);

void push_into_ostack(vm_ostack_t **stack, vm_ostack_t **new_frame);
vm_ostack_t * pop_from_ostack(vm_ostack_t **stack);

#endif /* VM_FRAME_H */
