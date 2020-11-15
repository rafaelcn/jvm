#ifndef VM_INNER_CLASSES_H
#define VM_INNER_CLASSES_H

#include <stdint.h>

/**
 * @brief A classes structure.
 */
typedef struct vm_classes {
    uint16_t inner_class_info_index;
    uint16_t outer_class_info_index;
    uint16_t inner_name_index;
    uint16_t inner_class_access_flags;
} vm_classes_t;

/**
 * @brief A inner_classes structure.
 */
typedef struct vm_inner_classes {
    uint16_t number_of_classes;
    vm_classes_t *classes;
} vm_inner_classes_t;

#endif /* VM_INNER_CLASSES_H */
