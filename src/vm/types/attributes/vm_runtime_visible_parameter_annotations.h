#ifndef VM_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS_H
#define VM_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS_H

#include "vm_runtime_visible_annotations.h"

/**
 * @brief A parameter_annotations structure.
 */
typedef struct vm_parameter_annotations {
        uint16_t num_annotations;
        vm_annotation_t *annotations;
    } vm_parameter_annotations_t;

/**
 * @brief A runtime_visible_parameter_annotations structure.
 */
typedef struct vm_runtime_visible_parameter_annotations {
    uint8_t num_parameters;
    vm_parameter_annotations_t *parameter_annotations;
} vm_runtime_visible_parameter_annotations_t;

#endif /* VM_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS_H */
