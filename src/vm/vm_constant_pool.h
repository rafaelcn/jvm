#ifndef VM_CONSTANT_POOL_H
#define VM_CONSTANT_POOL_H

#include <stdlib.h>
#include <stdint.h>

#include "vm_file.h"

typedef uint16_t class_flags_t;
typedef uint16_t method_flags_t;

/*
// ACC_PUBLIC may be accessed from outside its package.
const class_flags_t CLASS_PUBLIC = 0x0001;
// ACC_FINAL implies that no subclasses are allowed.
const class_flags_t CLASS_FINAL = 0x0010;
// ACC_INTERFACE implies that the defined file is an interface instead of a
// class. If this flag is not defined then the given file is a class.
const class_flags_t CLASS_INTERFACE = 0x0200;
// ACC_ABSTRACT implies that the class won't allow instantiation
const class_flags_t CLASS_ABSTRACT = 0x0400;
// ACC_SYNTHETIC implies that the class is not present in the source code,
// meaning it is an anonymous class.
const class_flags_t CLASS_SYNTHETIC  = 0x1000;
// ACC_ANNOTATION implies annotation type.
const class_flags_t CLASS_ANNOTATION = 0x2000;
// ACC_ENUM implies it has enum type.
const class_flags_t CLASS_ENUM = 0x4000;

const method_flags_t METHOD_PUBLIC = 0x0001;
*/

typedef union vm_field_info {

} vm_field_info;

/**
 * @brief
 */
typedef struct vm_cp_t {

} vm_cp_t;

/**
 * @brief
 */
typedef struct vm_cp_info_t {
    uint8_t tag;
    uint8_t info[];
} vm_cp_info_t;

/**
 * @brief
 */
typedef struct vm_field_info_t {
    class_flags_t access_flag;

} vm_field_info_t;

/**
 * @brief
 */
typedef struct vm_method_info_t {
    method_flags_t access_flag;
    uint16_t name_index;
    uint16_t descriptor_index;
    // array of size
    uint16_t attributes_count[];

} vm_method_info_t;

/**
 * @brief
 */
typedef struct vm_attribute_info_t {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    // array of size
    uint8_t info[];
} vm_attribute_info_t;

/**
 * @brief
 */
typedef struct vm_class_file_t {
    uint64_t magic;
    uint16_t minor;
    uint16_t major;

    uint16_t constant_pool_count_t;
    // The actual size of constant_pool_info_t is
    // sizeof(constant_pool_info_t/4)-1
    vm_cp_info_t *constant_pool;

    //struct vm_class_file_t* _this;
    //struct vm_class_file_t* _super;

    //class_flags_t access_flag;

    /**
     * At this point I can't evaluate if this implementation is correct because
     * of the size it can take in RAM. I could use a pointer to a linked list
     * of type T to implement interfaces, fields_info, methods_info etc.
     */

    /*uint16_t interfaces_count;
    uint16_t interfaces[UINT16_MAX];

    uint16_t fields_count;
    vm_field_info_t fields_info[UINT16_MAX];

    uint16_t methods_count;
    vm_method_info_t methods_info[UINT16_MAX];

    uint16_t attributes_count;
    vm_attribute_info_t attributes_info[UINT16_MAX];*/
} vm_class_file_t;

/**
 * @brief
 */
void vm_load_constant_pool(file_t *file);

#endif /* VM_CONSTANT_POOL_H */