#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <stdlib.h>
#include <stdint.h>

#include "vm_file.h"
#include "types/cp/vm_cp_types.h"
#include "types/attributes/vm_attribute_types.h"
#include "vm_constant_pool.h"


/**
 * @brief
 */
typedef struct vm_operand_stack {
    uint32_t operand;
    vm_operand_stack *next;
} vm_operand_stack_t;

/**
 * @brief
 */
typedef struct vm_frame {
	vm_class_file_t *class_file;
	vm_cp_info_t *constant_pool;
	uint32_t operand_stack_count;
	vm_operand_stack_t *operand_stack;
	uint32_t local_variables_count;
	uint32_t *local_variables;
} vm_frame_t;

/**
 * @brief
 */
typedef struct vm_frame_stack {
    vm_frame_t *frame;
    vm_frame_stack *next;
} vm_frame_stack_t;


#endif /* VM_FRAME_H */