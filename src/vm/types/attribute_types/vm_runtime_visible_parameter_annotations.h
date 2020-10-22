#ifndef VM_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS_H
#define VM_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS_H

#include "vm_runtime_visible_annotations.h"

/**
 * @brief
 */
typedef struct vm_runtime_visible_parameter_annotations {
    uint8_t num_parameters;
    struct {
        uint16_t num_annotations;
        vm_annotation_t *annotations;
    } *parameter_annotations;
} vm_runtime_visible_parameter_annotations_t;

#endif /* VM_RUNTIME_VISIBLE_PARAMETER_ANNOTATIONS_H */
