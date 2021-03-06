#ifndef VM_EXCEPTIONS_H
#define VM_EXCEPTIONS_H

#include <stdint.h>

/**
 * @brief A exceptions structure.
 */
typedef struct vm_exceptions {
    uint16_t number_of_exceptions;
    uint16_t *exception_index_table;
} vm_exceptions_t;

#endif /* VM_EXCEPTIONS_H */
