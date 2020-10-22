#ifndef VM_TARGET_TYPES_H
#define VM_TARGET_TYPES_H

#include "vm_type_parameter_target.h"
#include "vm_supertype_target.h"
#include "vm_type_parameter_bound_target.h"
#include "vm_empty_target.h"
#include "vm_formal_parameter_target.h"
#include "vm_throws_target.h"
#include "vm_localvar_target.h"
#include "vm_catch_target.h"
#include "vm_offset_target.h"
#include "vm_type_argument_target.h"

/**
 * @brief
 */
typedef union vm_target {
    vm_type_parameter_target_t type_parameter_target;
    vm_supertype_target_t supertype_target;
    vm_type_parameter_bound_target_t type_parameter_bound_target;
    vm_empty_target_t empty_target;
    vm_formal_parameter_target_t formal_parameter_target;
    vm_throws_target_t throws_target;
    vm_localvar_target_t localvar_target;
    vm_catch_target_t catch_target;
    vm_offset_target_t offset_target;
    vm_type_argument_target_t type_argument_target;
} vm_target_t;


#endif /* VM_TARGET_TYPES_H */
