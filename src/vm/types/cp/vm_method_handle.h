#ifndef VM_METHOD_HANDLE_H
#define VM_METHOD_HANDLE_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_method_handle {
    uint8_t reference_kind;
    uint16_t reference_index;
} vm_method_handle_t;

#endif /* VM_METHOD_HANDLE_H */
