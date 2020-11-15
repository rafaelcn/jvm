#ifndef VM_LONG_H
#define VM_LONG_H

#include <stdint.h>

/**
 * @brief A long structure.
 */
typedef struct vm_long_t {
    uint32_t high_bytes;
    uint32_t low_bytes;
} vm_long_t;


/**
 * @brief Converts two uint32_t into a long int number.
 */
long vm_itol(uint32_t low, uint32_t high);

#endif /* VM_LONG_H */
