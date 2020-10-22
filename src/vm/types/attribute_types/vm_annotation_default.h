#ifndef VM_ANNOTATION_DEFAULT_H
#define VM_ANNOTATION_DEFAULT_H

#include "vm_runtime_visible_annotations.h"

/**
 * @brief
 */
typedef struct vm_annotation_default {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    vm_element_value_t default_value;
} vm_annotation_default_t;

#endif /* VM_ANNOTATION_DEFAULT_H */
