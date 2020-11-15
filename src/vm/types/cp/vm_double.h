#ifndef VM_DOUBLE_H
#define VM_DOUBLE_H

#include "vm_long.h"

/**
 * @brief A vm_double structure.
 */
typedef vm_long_t vm_double_t;

/**
 * @brief Converts two uint32_t into a double number following the IEEE754
 * specification.
 */
double vm_itod(uint32_t low, uint32_t high);

#endif /* VM_DOUBLE_H */
