#ifndef VM_CONSTANT_POOL_H
#define VM_CONSTANT_POOL_H

#include <stdlib.h>
#include <stdint.h>

#include "vm_file.h"
#include "types/cp/vm_cp_types.h"
#include "types/attributes/vm_attribute_types.h"


/**
 * @brief
 */
typedef struct vm_cp_info {
    uint8_t tag;
    vm_cp_types_t info;
} vm_cp_info_t;

/**
 * @brief
 */
typedef struct vm_field_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    vm_attribute_info_t *attributes;
} vm_field_info_t;

/**
 * @brief
 */
typedef vm_field_info_t vm_method_info_t;

/**
 * @brief
 */
typedef struct vm_class_file {
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;

    uint16_t constant_pool_count;
    vm_cp_info_t *constant_pool;

    uint16_t access_flags;
    uint16_t this_class;
    uint16_t super_class;

    uint16_t interfaces_count;
    uint16_t *interfaces;

    uint16_t fields_count;
    vm_field_info_t *fields;

    uint16_t methods_count;
    vm_method_info_t *methods;

    uint16_t attributes_count;
    vm_attribute_info_t *attributes;
} vm_class_file_t;

/**
 * @brief
 */
void vm_load_constant_pool(file_t *file);

#endif /* VM_CONSTANT_POOL_H */
