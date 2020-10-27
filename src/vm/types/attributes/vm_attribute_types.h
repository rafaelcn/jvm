#ifndef VM_ATTRIBUTE_TYPES_H
#define VM_ATTRIBUTE_TYPES_H

/**
 * Include all files of attribute_types into a single file.
 */
#include "vm_constant_value.h"
#include "vm_code.h"
#include "vm_stack_map_table.h"
#include "vm_exceptions.h"
#include "vm_inner_classes.h"
#include "vm_enclosing_method.h"
#include "vm_synthetic.h"
#include "vm_signature.h"
#include "vm_source_file.h"
#include "vm_source_debug_extension.h"
#include "vm_line_number_table.h"
#include "vm_local_variable_table.h"
#include "vm_local_variable_type_table.h"
#include "vm_deprecated.h"
#include "vm_runtime_visible_annotations.h"
#include "vm_runtime_invisible_annotations.h"
#include "vm_runtime_visible_parameter_annotations.h"
#include "vm_runtime_invisible_parameter_annotations.h"
#include "vm_runtime_visible_type_annotations.h"
#include "vm_runtime_invisible_type_annotations.h"
#include "vm_annotation_default.h"
#include "vm_bootstrap_methods.h"
#include "vm_method_parameters.h"

/**
 * @brief
 */
typedef union vm_attribute_types {
    vm_constant_value_t constantvalue_attribute;
    vm_code_t code_attribute;
    vm_stack_map_table_t stackmaptable_attribute;
    vm_exceptions_t exceptions_attribute;
    vm_inner_classes_t innerclasses_attribute;
    vm_enclosing_method_t enclosingmethod_attribute;
    vm_synthetic_t synthetic_attribute;
    vm_signature_t signature_attribute;
    vm_source_file_t sourcefile_attribute;
    vm_source_debug_extension_t sourcedebugextension_attribute;
    vm_line_number_table_t linenumbertable_attribute;
    vm_local_variable_table_t localvariabletable_attribute;
    vm_local_variable_type_table_t localvariabletypetable_attribute;
    vm_deprecated_t deprecated_attribute;
    vm_runtime_visible_annotations_t runtimevisibleannotations_attribute;
    vm_runtime_invisible_annotations_t runtimeinvisibleannotations_attribute;
    vm_runtime_visible_parameter_annotations_t runtimevisibleparameterannotations_attribute;
    vm_runtime_invisible_parameter_annotations_t runtimeinvisibleparameterannotations_attribute;
    vm_runtime_visible_type_annotations_t runtimevisibletypeannotations_attribute;
    vm_runtime_invisible_type_annotations_t runtimeinvisibletypeannotations_attribute;
    vm_annotation_default_t annotationdefault_attribute;
    vm_bootstrap_methods_t bootstrapmethods_attribute;
    vm_method_parameters_t methodparameters_attribute;
} vm_attribute_types_t;

#endif /* VM_ATTRIBUTE_TYPES_H */
