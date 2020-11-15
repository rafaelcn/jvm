#ifndef VM_VERIFICATION_TYPE_H
#define VM_VERIFICATION_TYPE_H

#include <stdint.h>

/**
 * @brief A top_variable structure.
 */
typedef struct vm_top_variable {
} vm_top_variable_t;

/**
 * @brief A integer_variable structure.
 */
typedef vm_top_variable_t vm_integer_variable_t;

/**
 * @brief A float_variable structure.
 */
typedef vm_top_variable_t vm_float_variable_t;

/**
 * @brief A long_variable structure.
 */
typedef vm_top_variable_t vm_long_variable_t;

/**
 * @brief A double_variable structure.
 */
typedef vm_top_variable_t vm_double_variable_t;

/**
 * @brief A null_variable structure.
 */
typedef vm_top_variable_t vm_null_variable_t;

/**
 * @brief A uninitialized_this_variable structure.
 */
typedef vm_top_variable_t vm_uninitialized_this_variable_t;

/**
 * @brief A bject_variable structure.
 */
typedef struct vm_object_variable {
    uint16_t cpool_index;
} vm_object_variable_t;

/**
 * @brief A uninitialized_variable structure.
 */
typedef struct vm_uninitialized_variable {
    uint16_t offset;
} vm_uninitialized_variable_t;

/**
 * @brief A verification_type_info structure.
 */
typedef struct vm_verification_type_info {
    uint8_t tag;

    union vm_variable_t {
        vm_top_variable_t top_variable;
        vm_integer_variable_t integer_variable;
        vm_float_variable_t float_variable;
        vm_long_variable_t long_variable;
        vm_double_variable_t double_variable;
        vm_null_variable_t null_variable;
        vm_uninitialized_this_variable_t uninitialized_this_variable;
        vm_object_variable_t object_variable;
        vm_uninitialized_variable_t uninitialized_variable;
    } variable;
} vm_verification_type_info_t;

#endif /* VM_VERIFICATION_TYPE_H */
