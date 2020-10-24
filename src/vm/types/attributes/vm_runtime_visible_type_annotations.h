#ifndef VM_RUNTIME_VISIBLE_TYPE_ANNOTATIONS_H
#define VM_RUNTIME_VISIBLE_TYPE_ANNOTATIONS_H

#include "vm_runtime_visible_annotations.h"
#include "../target/vm_target_types.h"

/**
 * @brief
 */
typedef struct vm_type_path {
    uint8_t path_length;
    struct {
        uint8_t type_path_kind;
        uint8_t type_argument_index;
    } *path;
} vm_type_path_t;

/**
 * @brief
 */
typedef struct vm_type_annotation {
    uint8_t target_type;
    vm_target_t target_info;
    vm_type_path_t target_path;
    uint16_t type_index;

    uint16_t num_element_value_pairs;
    struct {
        uint16_t element_name_index;
        vm_element_value_t value;
    } *element_value_pairs;
} vm_type_annotation_t;

/**
 * @brief
 */
typedef struct vm_runtime_visible_type_annotations {
    uint16_t num_annotations;
    vm_type_annotation_t *annotations;
} vm_runtime_visible_type_annotations_t;

#endif /* VM_RUNTIME_VISIBLE_TYPE_ANNOTATIONS_H */
