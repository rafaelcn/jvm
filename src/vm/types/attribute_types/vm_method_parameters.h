#ifndef VM_METHOD_PARAMETERS_H
#define VM_METHOD_PARAMETERS_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_method_parameters {
    uint8_t parameters_count;
    struct {
        uint16_t name_index;
        uint16_t access_flags;
    } *parameters;
} vm_method_parameters_t;

#endif /* VM_METHOD_PARAMETERS_H */
