#ifndef VM_VERIFICATION_TYPE_H
#define VM_VERIFICATION_TYPE_H

/**
 * @brief
 */
typedef struct vm_top_variable {
    uint8_t tag;
} vm_top_variable_t;

/**
 * @brief
 */
typedef vm_top_variable_t vm_integer_variable_t;

/**
 * @brief
 */
typedef vm_top_variable_t vm_float_variable_t;

/**
 * @brief
 */
typedef vm_top_variable_t vm_long_variable_t;

/**
 * @brief
 */
typedef vm_top_variable_t vm_double_variable_t;

/**
 * @brief
 */
typedef vm_top_variable_t vm_null_variable_t;

/**
 * @brief
 */
typedef vm_top_variable_t vm_uninitialized_this_variable_t;

/**
 * @brief
 */
typedef struct vm_object_variable {
    uint8_t tag;
    uint16_t cpool_index;
} vm_object_variable_t;

/**
 * @brief
 */
typedef struct vm_uninitialized_variable {
    uint8_t tag;
    uint16_t offset;
} vm_uninitialized_variable_t;

/**
 * @brief
 */
typedef union vm_verification_type_info {
    vm_top_variable_t top_variable;
    vm_integer_variable_t integer_variable;
    vm_float_variable_t float_variable;
    vm_long_variable_t long_variable;
    vm_double_variable_t double_variable;
    vm_null_variable_t null_variable;
    vm_uninitialized_this_variable_t uninitialized_this_variable;
    vm_object_variable_t object_variable;
    vm_uninitialized_variable_t uninitialized_variable;
} vm_verification_type_info_t;

#endif /* VM_VERIFICATION_TYPE_H */
