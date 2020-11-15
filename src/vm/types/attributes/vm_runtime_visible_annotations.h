#ifndef VM_RUNTIME_VISIBLE_ANNOTATIONS_H
#define VM_RUNTIME_VISIBLE_ANNOTATIONS_H

#include <stdint.h>

/**
 * @brief A element_value_pairs structure.
 */
typedef struct vm_element_value_pairs vm_element_value_pairs_t;

/**
 * @brief A element_value structure.
 */
typedef struct vm_element_value {
    uint8_t tag;
    union {
        uint16_t const_value_index;

        struct {
            uint16_t type_name_index;
            uint16_t const_name_index;
        } enum_const_value;

        uint16_t class_info_index;

        struct vm_annotation_t {
            uint16_t type_index;
            uint16_t num_element_value_pairs;

            vm_element_value_pairs_t *element_value_pairs;
        } annotation_value;

        struct {
            uint16_t num_values;
            struct vm_element_value *values;
        } array_value;
    } value;
} vm_element_value_t;

/**
 * @brief A element_value_pairs structure.
 */
struct vm_element_value_pairs {
    uint16_t element_name_index;
    vm_element_value_t value;
};

/**
 * @brief A annotation structure.
 */
typedef struct vm_annotation {
    uint16_t type_index;
    uint16_t num_element_value_pairs;

    vm_element_value_pairs_t *element_value_pairs;
} vm_annotation_t;


/**
 * @brief A runtime_visible_annotations structure.
 */
typedef struct vm_runtime_visible_annotations {
    uint16_t num_annotations;
    vm_annotation_t *annotations;
} vm_runtime_visible_annotations_t;

#endif /* VM_RUNTIME_VISIBLE_ANNOTATIONS_H */
