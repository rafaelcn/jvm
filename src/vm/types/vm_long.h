#ifndef VM_LONG_H
#define VM_LONG_H

#include <stdint.h>

/**
 * @brief
 */
typedef struct vm_long_t {
    uint32_t high_bytes;
    uint32_t low_bytes;
} vm_long_t;

#endif /* VM_LONG_H */