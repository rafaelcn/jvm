#ifndef VM_CONSTANT_POOL_H
#define VM_CONSTANT_POOL_H

#include <stdlib.h>
#include <stdint.h>

#include "vm_file.h"
#include "types/cp/vm_cp_types.h"
#include "types/attributes/vm_attribute_types.h"


/**
 * @brief Constant Pool entry strcuture.
 */
typedef struct vm_cp_info {
    uint8_t tag;
    vm_cp_types_t info;
} vm_cp_info_t;

/**
 * @brief A Field_info structure.
 */
typedef struct vm_field_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    vm_attribute_info_t *attributes;
} vm_field_info_t;

/**
 * @brief A Method_info structure.
 */
typedef vm_field_info_t vm_method_info_t;

/**
 * @brief A ClassFile structure.
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
 * @brief Prints the information contained in the ClassFile structure in a
 * formatted manner.
 * @param class_file A ClassFile structure to be printed.
 * @param file A FILE (from stdio, in rb mode) pointer to a .class file.
 */
void class_file_reader(vm_class_file_t class_file, file_t *file);

/**
 * @brief Parses the .class bytecode to a ClassFile structure.
 * @param file A FILE (from stdio, in rb mode) pointer to a .class file.
 * @param cf A pointer to a ClassFile structure.
 */
void class_file_parser(file_t *file, vm_class_file_t *cf);

/**
 * @brief A function dedicated to filling the constant_pool field of the
 * vm_class_file_t structure.
 * @param file A file_t pointer that has the .class loaded.
 * @param cf A pointer to a vm_class_file_t structure.
 */
void constant_pool_parser(file_t *file, vm_class_file_t *cf);

/**
 * @brief A function that parses the constant pool entry tag to a string
 * in order to be printed by the class_file_reader.
 */
void vm_init_tag_map();

/**
 * @brief A function dedicated to filling the interfaces field of the
 * vm_class_file_t structure.
 * @param file A file_t pointer that has the .class loaded.
 * @param cf A pointer to a vm_class_file_t structure.
 */
void interfaces_parser(file_t *file, vm_class_file_t *cf);

/**
 * @brief A function dedicated to converting a Utf8 entry at the constant pool
 * to a int that can be used at a switch case.
 * @param length The length field of a Utf8_info structure.
 * @param bytes The bytes field of a Utf8_info structure.
 * @returns An int representing the attribute name, -1 if the attribute name
 * is unknown.
 */
int attribute_name_to_int(uint16_t length, uint8_t *bytes);

/**
 * @brief A function dedicated to fill stack variable
 *  at different union elements depending on the tag value.
 * @param stack A pointer to a vm_verification_type_info_t structure.
 * @param file A file_t pointer that has the .class loaded.
 */
void verification_type_parser(vm_verification_type_info_t *stack, file_t *file);

/**
 * @brief A function dedicated to fill entry stack map frame variable
 *  at different union elements depending on the frame
 * @param entry A pointer to a vm_stack_map_frame_t structure.
 * @param file A file_t pointer that has the .class loaded.
 */
void stack_map_frame_parser(vm_stack_map_frame_t *entry, file_t *file);

/**
 * @brief A function dedicated to fill entry stack map frame variable
 *  at different union elements depending on the frame
 * @param stack_map_table A pointer to a vm_stack_map_table_t structure.
 * @param file A file_t pointer that has the .class loaded.
 */
void stack_map_table_parser(vm_stack_map_table_t *stack_map_table, file_t *file);

/**
 * @brief A function that helps filling the varoius types of RuntimeAnnotations
 * in the Attributes fields of a vm_class_file_t structure.
 * @param element_value_pt A pointer to a vm_element_value_t structure.
 * @param file A file_t pointer that has the .class loaded.
 */
void element_value_parser(vm_element_value_t *element_value_pt, file_t *file);

/**
 * @brief A function that helps filling the varoius types of RuntimeAnnotations
 * in the Attributes fields of a vm_class_file_t structure.
 * @param element_value_pairs_count A uint16_t representing the amount of element_value_pairs.
 * @param element_value_pairs_pt A pointer to a vm_element_value_pairs_t structure.
 * @param file A file_t pointer that has the .class loaded.
 */
void element_value_pairs_parser(uint16_t element_value_pairs_count, vm_element_value_pairs_t *element_value_pairs_pt, file_t *file);

/**
 * @brief A function that helps filling the varoius types of RuntimeAnnotations
 * in the Attributes fields of a vm_class_file_t structure.
 * @param type_annotation_count A uint16_t representing the amount of type_annotations.
 * @param type_annotation_pt A pointer to a vm_type_annotation_t structure.
 * @param file A file_t pointer that has the .class loaded.
 */
void type_annotations_parser(uint16_t type_annotation_count, vm_type_annotation_t *type_annotation_pt, file_t *file);

/**
 * @brief A function dedicated to filling the attributes fields of the
 * vm_class_file_t structure.
 * @param attributes_count A uint16_t representing the amount of attributes.
 * @param attributes A pointer to a vm_attribute_info_t structure;
 * @param constant_pool A pointer to a vm_cp_info_t structure.
 * @param file A file_t pointer that has the .class loaded.
 */
void attributes_parser(uint16_t attributes_count, vm_attribute_info_t *attributes, vm_cp_info_t *constant_pool, file_t *file);

/**
 * @brief A function dedicated to filling the fields field of the
 * vm_class_file_t structure.
 * @param file A file_t pointer that has the .class loaded.
 * @param cf A pointer to a vm_class_file_t structure.
 */
void fields_parser(file_t *file, vm_class_file_t *cf);

/**
 * @brief A function dedicated to filling the methods field of the
 * vm_class_file_t structure.
 * @param file A file_t pointer that has the .class loaded.
 * @param cf A pointer to a vm_class_file_t structure.
 */
void methods_parser(file_t *file, vm_class_file_t *cf);

/**
 * @brief A function that helps printing the Java Modified UTF8.
 * @param length The length field of a Utf8_info structure.
 * @param bytes The bytes field of a Utf8_info structure.
 */
void utf8_helper(uint16_t length, uint8_t *bytes);

/**
 * @brief Prints the information contained in the ClassFile structure in a
 * formatted manner.
 * @param class_file A ClassFile structure to be printed.
 * @param file A file_t pointer that has the .class loaded.
 */
void class_file_reader(vm_class_file_t class_file, file_t *file);

#endif /* VM_CONSTANT_POOL_H */
