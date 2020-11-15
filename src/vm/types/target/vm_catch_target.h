#ifndef VM_CATCH_TARGET_H
#define VM_CATCH_TARGET_H

#include <stdint.h>

/**
 * @brief A catch_target structure.
 */
typedef struct vm_catch_target {
    uint16_t exception_table_index;
} vm_catch_target_t;

#endif /* VM_CATCH_TARGET_H */
