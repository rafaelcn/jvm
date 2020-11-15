#ifndef VM_CP_STRING_H
#define VM_CP_STRING_H

#include <stdint.h>

/**
 * @brief Encode a string index.
 */
typedef struct vm_string_t
{
    uint16_t string_index;
} vm_string_t;

#endif /* VM_CP_STRING_H */
