#ifndef VM_CP_TYPES_H
#define VM_CP_TYPES_H

/**
 * Include all files of cp_types into a single file.
 */
#include "vm_class.h"
#include "vm_field.h"
#include "vm_method.h"
#include "vm_interface_method.h"
#include "vm_string.h"
#include "vm_integer.h"
#include "vm_float.h"
#include "vm_long.h"
#include "vm_double.h"
#include "vm_name_and_type.h"
#include "vm_utf8.h"
#include "vm_method_handle.h"
#include "vm_method_type.h"
#include "vm_invoke_dynamic.h"

/**
 * @brief
 */
typedef union vm_cp_types {
    vm_class_t class_info;
    vm_field_ref_t fieldref_info;
    vm_method_ref_t methodref_info;
    vm_interface_method_ref_t interfacemethodref_info;
    vm_string_t string_info;
    vm_integer_t integer_info;
    vm_float_t float_info;
    vm_long_t long_info;
    vm_double_t double_info;
    vm_name_and_type_t nameandtype_info;
    vm_utf8_t utf8_info;
    vm_method_handle_t methodhandle_info;
    vm_method_type_t methodtype_info;
    vm_invoke_dynamic_t invokedynamic_info;
} vm_cp_types_t;

#endif /* VM_CP_TYPES_H */
