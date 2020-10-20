#ifndef VM_ENCLOSING_METHOD_H
#define VM_ENCLOSING_METHOD_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_enclosing_method {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t class_index;
    uint16_t method_index;
} vm_enclosing_method_t;

#endif /* VM_ENCLOSING_METHOD_H */
