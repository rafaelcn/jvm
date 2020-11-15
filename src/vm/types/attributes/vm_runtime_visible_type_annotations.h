#ifndef VM_RUNTIME_VISIBLE_TYPE_ANNOTATIONS_H
#define VM_RUNTIME_VISIBLE_TYPE_ANNOTATIONS_H

#include "vm_runtime_visible_annotations.h"
#include "../target/vm_target_types.h"


/**
 * @brief A type_path_table structure.
 */
typedef struct vm_type_path_table {
        uint8_t type_path_kind;
        uint8_t type_argument_index;
    } vm_type_path_table_t;


/**
 * @brief A type_path structure.
 */
typedef struct vm_type_path {
    uint8_t path_length;
    vm_type_path_table_t *path;
} vm_type_path_t;

/**
 * @brief A type_annotation structure.
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
 * @brief Aruntime_visible_type_annotations structure.
 */
typedef struct vm_runtime_visible_type_annotations {
    uint16_t num_annotations;
    vm_type_annotation_t *annotations;
} vm_runtime_visible_type_annotations_t;

#endif /* VM_RUNTIME_VISIBLE_TYPE_ANNOTATIONS_H */
