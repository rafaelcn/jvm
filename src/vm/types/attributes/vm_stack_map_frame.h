#ifndef VM_STACK_MAP_FRAME_H
#define VM_STACK_MAP_FRAME_H

#include <stdint.h>

#include "vm_verification_type.h"

/**
 * @brief
 */
typedef struct vm_same_frame {
} vm_same_frame_t;

/**
 * @brief
 */
typedef struct vm_same_locals_1_stack_item_frame {
    vm_verification_type_info_t stack;
} vm_same_locals_1_stack_item_frame_t;

/**
 * @brief
 */
typedef struct vm_same_locals_1_stack_item_frame_extended {
    uint16_t offset_delta;
    vm_verification_type_info_t stack;
} vm_same_locals_1_stack_item_frame_extended_t;

/**
 * @brief
 */
typedef struct vm_chop_frame {
    uint16_t offset_delta;
} vm_chop_frame_t;

/**
 * @brief
 */
typedef vm_chop_frame_t vm_same_frame_extended_t;

/**
 * @brief
 */
typedef struct vm_append_frame {
    uint16_t offset_delta;
    vm_verification_type_info_t *locals;
} vm_append_frame_t;

/**
 * @brief
 */
typedef struct vm_full_frame {
    uint16_t offset_delta;

    uint16_t number_of_locals;
    vm_verification_type_info_t *locals;

    uint16_t number_of_stack_items;
    vm_verification_type_info_t *stack;
} vm_full_frame_t;

/**
 * @brief
 */
typedef struct vm_stack_map_frame {
    uint8_t frame_type;

    union {
        vm_same_frame_t same_frame;
        vm_same_locals_1_stack_item_frame_t same_locals_1_stack_item_frame;
        vm_same_locals_1_stack_item_frame_extended_t same_locals_1_stack_item_frame_extended;
        vm_chop_frame_t chop_frame;
        vm_same_frame_extended_t same_frame_extended;
        vm_append_frame_t append_frame;
        vm_full_frame_t full_frame;
    } frame;
} vm_stack_map_frame_t;

#endif /* VM_STACK_MAP_FRAME_H */
