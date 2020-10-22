#ifndef VM_RUNTIME_VISIBLE_ANNOTATIONS_H
#define VM_RUNTIME_VISIBLE_ANNOTATIONS_H

#include <stdint.h>

typedef struct vm_element_value {
    uint8_t tag;
    union {
        uint16_t const_value_index;

        struct {
            uint16_t type_name_index;
            uint16_t const_name_index;
        } enum_const_value;

        uint16_t class_info_index;

        vm_annotation_t annotation_value;

        struct {
            uint16_t num_values;
            vm_element_value_t *values;
        } array_value;
    } value;
} vm_element_value_t;


/**
 * @brief
 */
typedef struct vm_annotation {
    uint16_t type_index;
    uint16_t num_element_value_pairs;

    struct {
        uint16_t element_name_index;
        vm_element_value_t value;
    } *element_value_pairs;
} vm_annotation_t;


/**
 * @brief
 */
typedef struct vm_runtime_visible_annotations {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t num_annotations;
    vm_annotation_t *annotations;
} vm_runtime_visible_annotations_t;

#endif /* VM_RUNTIME_VISIBLE_ANNOTATIONS_H */
