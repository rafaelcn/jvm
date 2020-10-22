#ifndef VM_FLOAT_T
#define VM_FLOAT_T

#include <stdint.h>

#include "vm_integer.h"

/**
 * @brief
 */
typedef vm_integer_t vm_float_t;

/**
 * @brief Converts an uint32_t to a float number following the IEEE754
 * specification.
 */
float vm_itof(uint32_t bytes);

#endif /* VM_FLOAT_T */