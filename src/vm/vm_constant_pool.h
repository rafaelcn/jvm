#ifndef VM_CONSTANT_POOL_H
#define VM_CONSTANT_POOL_H

#include <stdlib.h>
#include <stdint.h>

// acess_flag_t is a number representing the state of a class (?)
typedef uint16_t access_flag_t;

/**
 * @brief
 */
struct vm_constant_pool_t {

};

/**
 * @brief
 */
struct vm_constant_pool_info_t {
    uint8_t tag;
    uint8_t info[];
};

/**
 * @brief
 */
struct vm_field_info_t {};
/**
 * @brief
 */
struct vm_method_info_t {};
/**
 * @brief
 */
struct vm_attribute_info_t {

};

/**
 * @brief
 */
struct vm_class_file_t {
    uint64_t magic;
    uint16_t minor;
    uint16_t major;

    vm_class_file_t* _this;
    vm_class_file_t* _super;

    access_flag_t access_flag;

    /**
     * At this point I can't evaluate if this implementation is correct because
     * of the size it can take in RAM. I could use a pointer to a linked list
     * of type T to implement interfaces, fields_info, methods_info etc.
     */

    uint16_t interfaces_count;
    uint16_t interfaces[UINT16_MAX];

    uint16_t fields_count;
    vm_field_info_t fields_info[UINT16_MAX];

    uint16_t methods_count;
    vm_method_info_t methods_info[UINT16_MAX];

    uint16_t attributes_count;
    vm_attribute_info_t attributes_info[UINT16_MAX];

    uint16_t constanpool_count_t;
    // The actual size of constanpool_info_t is sizeof(constanpool_info_t/4)-1
    vm_constant_pool_info_t constant_pool_info[];
};

// ACC_PUBLIC may be accessed from outside its package.
const access_flag_t ACC_PUBLIC = 0x0001;
// ACC_FINAL implies that no subclasses are allowed.
const access_flag_t ACC_FINAL  = 0x0010;
// ACC_INTERFACE implies that the defined file is an interface instead of a
// class. If this flag is not defined then the given file is a class.
const access_flag_t ACC_INTERFACE = 0x0200;
// ACC_ABSTRACT implies that the class won't allow instantiation
const access_flag_t ACC_ABSTRACT  = 0x0400;
// ACC_SYNTHETIC implies that the class is not present in the source code,
// meaning it is an anonymous class.
const access_flag_t ACC_SYNTHETIC  = 0x1000;
// ACC_ANNOTATION implies annotation type.
const access_flag_t ACC_ANNOTATION  = 0x2000;
// ACC_ENUM implies it has enum type.
const access_flag_t ACC_ENUM  = 0x4000;

#endif /* VM_CONSTANT_POOL_H */