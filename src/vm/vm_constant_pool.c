#include "vm_constant_pool.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "vm_file.h"

#include "utils/vm_target.h"

/**
 * @brief Constant Pool tag mapping.
 */
#define CONSTANT_Class              (0x07)
#define CONSTANT_Fieldref           (0x09)
#define CONSTANT_Methodref          (0x0A)
#define CONSTANT_InterfaceMethodref (0x0B)
#define CONSTANT_String             (0x08)
#define CONSTANT_Integer            (0x03)
#define CONSTANT_Float              (0x04)
#define CONSTANT_Long               (0x05)
#define CONSTANT_Double             (0x06)
#define CONSTANT_NameAndType        (0x0C)
#define CONSTANT_Utf8               (0x01)
#define CONSTANT_MethodHandle       (0x0F)
#define CONSTANT_MethodType         (0x10)
#define CONSTANT_InvokeDynamic      (0x12)

/**
 * @brief Attribute Types tag mapping.
 */
enum attribute_types_enum {
    ConstantValue,
    Code,
    StackMapTable,
    Exceptions,
    InnerClasses,
    EnclosingMethod,
    Synthetic,
    Signature,
    SourceFile,
    SourceDebugExtension,
    LineNumberTable,
    LocalVariableTable,
    LocalVariableTypeTable,
    Deprecated,
    RuntimeVisibleAnnotations,
    RuntimeInvisibleAnnotations,
    RuntimeVisibleParameterAnnotations,
    RuntimeInvisibleParameterAnnotations,
    RuntimeVisibleTypeAnnotations,
    RuntimeInvisibleTypeAnnotations,
    AnnotationDefault,
    BootstrapMethods,
    MethodParameters
} attribute_types_enum;

/**
 * @brief An array containing the respective string correspondents of the
 * constant pool tags.
 */
char *tag_constants[19];

void vm_init_tag_map() {
    for (size_t i = 0; i < 19; i++) {
        // each tag_constant position can hold up to 17 chars, the exact amount
        // is needed for the largest constant pool tag string to fit.
        tag_constants[i] = calloc(17, sizeof(char));
    }

    strcpy(tag_constants[0x01], "UTF8");
    strcpy(tag_constants[0x03], "Integer");
    strcpy(tag_constants[0x04], "Float");
    strcpy(tag_constants[0x05], "Long");
    strcpy(tag_constants[0x06], "Double");
    strcpy(tag_constants[0x07], "Class");
    strcpy(tag_constants[0x08], "String");
    strcpy(tag_constants[0x09], "Field");
    strcpy(tag_constants[0x0A], "Method");
    strcpy(tag_constants[0x0B], "Interface Method");
    strcpy(tag_constants[0x0C], "Name and Type");
    strcpy(tag_constants[0x0F], "Method Handle");
    strcpy(tag_constants[0x10], "Method Type");
    strcpy(tag_constants[0x12], "Invoke Dynamic");
}

/**
 * @brief A function dedicated to filling the constant_pool field of the
 * vm_class_file_t structure.
 * @param file A file_t pointer that has the .class loaded.
 * @param cf A pointer to a vm_class_file_t structure.
 */
void constant_pool_parser(file_t *file, vm_class_file_t *cf) {
    uint8_t tag;

    for (int i = 0; i < (cf->constant_pool_count - 1); i++) {
        tag = read_u1(file);

        switch (tag) {
        case CONSTANT_Class:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.class_info.name_index = read_u2(file);
            break;

        case CONSTANT_Fieldref:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.fieldref_info.class_index = read_u2(file);
            cf->constant_pool[i].info.fieldref_info.name_and_type_index = read_u2(file);
            break;

        case CONSTANT_Methodref:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.methodref_info.class_index = read_u2(file);
            cf->constant_pool[i].info.methodref_info.name_and_type_index = read_u2(file);
            break;

        case CONSTANT_InterfaceMethodref:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.interfacemethodref_info.class_index = read_u2(file);
            cf->constant_pool[i].info.interfacemethodref_info.name_and_type_index = read_u2(file);
            break;

        case CONSTANT_String:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.string_info.string_index = read_u2(file);
            break;

        case CONSTANT_Integer:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.integer_info.bytes = read_u4(file);
            break;

        case CONSTANT_Float:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.float_info.bytes = read_u4(file);
            break;

        case CONSTANT_Long:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.long_info.high_bytes = read_u4(file);
            cf->constant_pool[i].info.long_info.low_bytes = read_u4(file);
            break;

        case CONSTANT_Double:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.double_info.high_bytes = read_u4(file);
            cf->constant_pool[i].info.double_info.low_bytes = read_u4(file);
            break;

        case CONSTANT_NameAndType:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.nameandtype_info.name_index = read_u2(file);
            cf->constant_pool[i].info.nameandtype_info.descriptor_index = read_u2(file);
            break;

        case CONSTANT_Utf8:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.utf8_info.length = read_u2(file);
            cf->constant_pool[i].info.utf8_info.bytes = (uint8_t*) calloc(
                cf->constant_pool[i].info.utf8_info.length, sizeof(uint8_t));

            uint16_t size = cf->constant_pool[i].info.utf8_info.length;

            for(int j = 0; j < size; j++) {
                cf->constant_pool[i].info.utf8_info.bytes[j] = read_u1(file);
            }
            break;

        case CONSTANT_MethodHandle:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.methodhandle_info.reference_kind = read_u1(file);
            cf->constant_pool[i].info.methodhandle_info.reference_index = read_u2(file);
            break;

        case CONSTANT_MethodType:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.methodtype_info.desciptor_index = read_u2(file);
            break;

        case CONSTANT_InvokeDynamic:
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.invokedynamic_info.bootstrap_method_attr_index = read_u2(file);
            cf->constant_pool[i].info.invokedynamic_info.name_and_type_index = read_u2(file);
            break;

        default:
            break;
        }
    }
}

/**
 * @brief A function dedicated to filling the interfaces field of the
 * vm_class_file_t structure.
 * @param file A file_t pointer that has the .class loaded.
 * @param cf A pointer to a vm_class_file_t structure.
 */
void interfaces_parser(file_t *file, vm_class_file_t *cf) {
    for (int i = 0; i < (cf->interfaces_count); i++) {
        cf->interfaces[i] = read_u2(file);
    }
}

/**
 * @brief A function dedicated to converting a Utf8 entry at the constant pool
 * to a int that can be used at a switch case.
 */
int attribute_name_to_int(uint16_t length, uint8_t *bytes) {
    uint16_t *heap = vm_utf8_to_uint16_t(length, bytes);
    char buffer[length];

    for (int j = 0; j < length; j++) {
        sprintf(&buffer[j], "%lc", heap[j]);
    }

    if (buffer == "ConstantValue")
        return ConstantValue;
    if (buffer == "Code")
        return Code;
    if (buffer == "StackMapTable")
        return StackMapTable;
    if (buffer == "Exceptions")
        return Exceptions;
    if (buffer == "InnerClasses")
        return InnerClasses;
    if (buffer == "EnclosingMethod")
        return EnclosingMethod;
    if (buffer == "Synthetic")
        return Synthetic;
    if (buffer == "Signature")
        return Signature;
    if (buffer == "SourceFile")
        return SourceFile;
    if (buffer == "SourceDebugExtension")
        return SourceDebugExtension;
    if (buffer == "LineNumberTable")
        return LineNumberTable;
    if (buffer == "LocalVariableTable")
        return LocalVariableTable;
    if (buffer == "LocalVariableTypeTable")
        return LocalVariableTypeTable;
    if (buffer == "Deprecated")
        return Deprecated;
    if (buffer == "RuntimeVisibleAnnotations")
        return RuntimeVisibleAnnotations;
    if (buffer == "RuntimeInvisibleAnnotations")
        return RuntimeInvisibleAnnotations;
    if (buffer == "RuntimeVisibleParameterAnnotations")
        return RuntimeVisibleParameterAnnotations;
    if (buffer == "RuntimeInvisibleParameterAnnotations")
        return RuntimeInvisibleParameterAnnotations;
    if (buffer == "RuntimeVisibleTypeAnnotations")
        return RuntimeVisibleTypeAnnotations;
    if (buffer == "RuntimeInvisibleTypeAnnotations")
        return RuntimeInvisibleTypeAnnotations;
    if (buffer == "AnnotationDefault")
        return AnnotationDefault;
    if (buffer == "BootstrapMethods")
        return BootstrapMethods;
    if (buffer == "MethodParameters")
        return MethodParameters;

    return -1;
}

/**
 * @brief
 */
void verification_type_parser(vm_verification_type_info_t *stack, file_t *file) {
    switch (stack->tag) {
    case 0: // ITEM_Top
        break;

    case 1: // ITEM_Integer
        break;

    case 2: // ITEM_Float
        break;

    case 5: // ITEM_Null
        break;

    case 6: // ITEM_UninitializedThis
        break;

    case 7: // ITEM_Object
        stack->variable.object_variable.cpool_index = read_u2(file);
        break;

    case 8: // ITEM_Uninitialized
        stack->variable.uninitialized_variable.offset = read_u2(file);
        break;

    case 4: // ITEM_Long
        break;

    case 3: // ITEM_Double
        break;

    default:
        break;
    }
}

/**
 * @brief
 */
void stack_map_frame_parser(vm_stack_map_frame_t *entry, file_t *file) {
    if (entry->frame_type >= 0 && entry->frame_type <= 63) {
        // SAME FRAME
    }
    else if (entry->frame_type >= 64 && entry->frame_type <= 127) {
        // SAME_LOCALS_1_STACK_ITEM
        entry->frame.same_locals_1_stack_item_frame.stack.tag = read_u1(file);
        verification_type_parser(&entry->frame.same_locals_1_stack_item_frame.stack, file);
    }
    else if (entry->frame_type == 247) {
        // SAME_LOCALS_1_STACK_ITEM_EXTENDED
        entry->frame.same_locals_1_stack_item_frame_extended.offset_delta = read_u2(file);
        verification_type_parser(&entry->frame.same_locals_1_stack_item_frame_extended.stack, file);
    }
    else if (entry->frame_type >= 248 && entry->frame_type <= 250) {
        // CHOP
        entry->frame.chop_frame.offset_delta = read_u2(file);
    }
    else if (entry->frame_type == 250) {
        // SAME_FRAME_EXTENDED
        entry->frame.same_frame_extended.offset_delta = read_u2(file);
    }
    else if (entry->frame_type >= 252 && entry->frame_type <= 254) {
        // APPEND
        entry->frame.append_frame.offset_delta = read_u2(file);
        entry->frame.append_frame.locals = calloc((entry->frame_type - 251),
            sizeof (vm_verification_type_info_t));

        for (int i = 0; i < (entry->frame_type - 251); i++) {
            entry->frame.append_frame.locals[i].tag = read_u1(file);
            verification_type_parser(&entry->frame.append_frame.locals[i], file);
        }
    }
    else if (entry->frame_type == 255) {
        // FULL_FRAME
        entry->frame.full_frame.offset_delta = read_u2(file);
        entry->frame.full_frame.number_of_locals = read_u2(file);
        entry->frame.full_frame.locals = calloc(entry->frame.full_frame.number_of_locals,
            sizeof (vm_verification_type_info_t));

        for (int i = 0; i < (entry->frame.full_frame.number_of_locals); i++) {
            entry->frame.full_frame.locals[i].tag = read_u1(file);
            verification_type_parser(&entry->frame.full_frame.locals[i], file);
        }

        entry->frame.full_frame.number_of_stack_items = read_u2(file);
        entry->frame.full_frame.stack = calloc(entry->frame.full_frame.number_of_stack_items,
            sizeof (vm_verification_type_info_t));

        for (int i = 0; i < (entry->frame.full_frame.number_of_stack_items); i++) {
            entry->frame.full_frame.stack[i].tag = read_u1(file);
            verification_type_parser(&entry->frame.full_frame.stack[i], file);
        }
    }
}

/**
 * @brief
 */
void stack_map_table_parser(vm_stack_map_table_t *stack_map_table, file_t *file) {
    for (int i = 0; i < (stack_map_table->number_of_entries); i++) {
        stack_map_table->entries[i].frame_type = read_u1(file);
        stack_map_frame_parser(&stack_map_table->entries[i], file);
    }
}

/**
 * @brief A function dedicated to filling the attributes field of the
 * vm_class_file_t structure.
 * @param element_value_pt 
 * @param file A file_t pointer that has the .class loaded.
 */
void element_value_parser(
    vm_element_value_t *element_value_pt, file_t *file)
{
    element_value_pt->tag = read_u1(file);
    uint8_t tag = element_value_pt->tag;
    
    // As the same behavior shall happen with different tags, let's compare the tag 
    // with those characters 
    uint8_t is_constant_value_index_tag = strchr("BCDFIJSZs", tag) != NULL;
    if(is_constant_value_index_tag) 
    {
        element_value_pt->value.const_value_index = read_u2(file);
    } else if (tag == 'e')
    {
        // Enum type
        element_value_pt->value.enum_const_value.type_name_index = read_u2(file);
        element_value_pt->value.enum_const_value.const_name_index = read_u2(file);
    } else if (tag == 'c')
    {
        // Class
        element_value_pt->value.class_info_index = read_u2(file);
    } else if (tag == '@')
    {
        // Annotation type(This one seems messy)
        element_value_pt->value.annotation_value.type_index = read_u2(file);
        element_value_pt->value.annotation_value.num_element_value_pairs = read_u2(file);
        element_value_pt->value.annotation_value.element_value_pairs = calloc(
            element_value_pt->value.annotation_value.num_element_value_pairs,
            sizeof (vm_element_value_pairs_t));

        // For some reason it was not accepting just pasing the pointer directly
        // Also this line bellow seems to still raise a warning.
        vm_element_value_pairs_t *temporary_pair = element_value_pt->value.annotation_value.element_value_pairs;
        element_value_pairs_parser(
            element_value_pt->value.annotation_value.num_element_value_pairs,
            temporary_pair,
            file);
    } else if (tag == '[')
    {
        // Array type(Also messy, what were those guys
        // thinking?)
        element_value_pt->value.array_value.num_values = read_u2(file);
        element_value_pt->value.array_value.values = calloc(
            element_value_pt->value.array_value.num_values,
            sizeof (vm_element_value_t));
        for(uint16_t l = 0;( l < element_value_pt->value.array_value.num_values); l++)
        {
            element_value_parser(&(element_value_pt->value.array_value.values[l]), file);
        }
    } else {
        printf("RuntimeVisibleAnnotations element pairs tag not found.");
    }
}

/**
 * @brief A function dedicated to filling the attributes field of the
 * vm_class_file_t structure.
 * @param element_value_pairs_count
 * @param element_value_pairs_pt
 * @param file A file_t pointer that has the .class loaded.
 */
void element_value_pairs_parser(
    uint16_t element_value_pairs_count,
    vm_element_value_pairs_t *element_value_pairs_pt, file_t *file)
{
    for(int k = 0; k < (element_value_pairs_count); k++)
    {
        element_value_pairs_pt[k].element_name_index = read_u2(file);
        element_value_parser(&(element_value_pairs_pt[k].value), file);
    }
}

/**
 * @brief A function dedicated to filling the attributes field of the
 * vm_class_file_t structure.
 * @param type_annotation_count
 * @param type_annotation_pt
 * @param file A file_t pointer that has the .class loaded.
 */
void type_annotations_parser(
    uint16_t type_annotation_count,
    vm_type_annotation_t *type_annotation_pt, file_t *file)
{
    for(uint16_t j = 0; j < (type_annotation_count); j++)
    {
        type_annotation_pt[j].target_type = read_u1(file);
        switch (type_annotation_pt[j].target_type)
        {
        case 0x00:
            // type parameter declaration of generic class or interface
            // Location: ClassFile
            type_annotation_pt[j].target_info.type_argument_target.type_argument_index = read_u1(file);

            break;
        case 0x01:
            // type parameter declaration of generic method or
            // constructor
            // Location: method_info
            type_annotation_pt[j].target_info.type_argument_target.type_argument_index = read_u1(file);
            break;
        case 0x10:
            // type in extends clause of class or interface declaration, or
            // in implements clause of interface declaration
            // Location: ClassFile
            type_annotation_pt[j].target_info.supertype_target.supertype_index = read_u2(file);
            /* code */
            break;
        case 0x11:
            // type in bound of type parameter declaration of generic
            // class or interface
            // Location: ClassFile
            type_annotation_pt[j].target_info.type_parameter_bound_target.type_parameter_index = read_u1(file);
            type_annotation_pt[j].target_info.type_parameter_bound_target.bound_index = read_u1(file);
            /* code */
            break;
        case 0x12:
            // 0x12 type in bound of type parameter declaration of generic method
            /* code */
            type_annotation_pt[j].target_info.type_parameter_bound_target.type_parameter_index = read_u1(file);
            type_annotation_pt[j].target_info.type_parameter_bound_target.bound_index = read_u1(file);
            break;
        case 0x13:
            // 0x13 type in field declaration field_info
            type_annotation_pt[j].target_info.empty_target;
            /* code */
            break;
        case 0x14:
            // 0x14 return type of method or constructor method_info
            type_annotation_pt[j].target_info.empty_target;
            /* code */
            break;
        case 0x15:
            // 0x15 receiver type of method or constructor method_info
            type_annotation_pt[j].target_info.empty_target;
            /* code */
            break;
        case 0x16:
            // 0x16 type in formal parameter declaration of method, constructor,
            // or lambda expression method_info
            type_annotation_pt[j].target_info.formal_parameter_target.formal_parameter_index = read_u1(file);
            /* code */
            break;
        case 0x17:
            // 0x17 type in throws clause of method or constructor method_info
            type_annotation_pt[j].target_info.throws_target.throws_type_index = read_u2(file);
            /* code */
            break;
        case 0x40:
        case 0x41:
            // 0x40 type in local variable declaration localvar_target
            // 0x41 type in resource variable declaration localvar_target
            type_annotation_pt[j].target_info.localvar_target.table_length = read_u2(file);
            type_annotation_pt[j].target_info.localvar_target.table = calloc(
                type_annotation_pt[j].target_info.localvar_target.table_length
                , sizeof (vm_localvar_table_t)
            );
            for(uint16_t k = 0; k < (type_annotation_pt[j].target_info.localvar_target.table_length); k++)
            {
                type_annotation_pt[j].target_info.localvar_target.table[k].start_pc = read_u2(file);
                type_annotation_pt[j].target_info.localvar_target.table[k].length = read_u2(file);
                type_annotation_pt[j].target_info.localvar_target.table[k].index = read_u2(file);
            }
            break;
        case 0x42:
            // 0x42 type in exception parameter declaration catch_target
            type_annotation_pt[j].target_info.catch_target.exception_table_index = read_u2(file);
            break;
        case 0x43:
            // 0x43 type in instanceof expression offset_target
        case 0x44:
            // 0x44 type in new expression offset_target
        case 0x45:
            //0x45 type in method reference expression using ::new
            // offset_target
        case 0x46:
            // 0x46 type in method reference expression using ::Identifier
            // offset_target
            type_annotation_pt[j].target_info.offset_target.offset = read_u2(file);
            break;
        case 0x47:
            // 0x47 type in cast expression type_argument_target
        case 0x48:
            // 0x48 type argument for generic constructor in new
            // expression or explicit constructor invocation statement
            // type_argument_target
        case 0x49:
            // 0x49 type argument for generic method in method
            // invocation expression
            // type_argument_target
        case 0x4A:
            // 0x4A type argument for generic constructor in method
            // reference expression using ::new type_argument_target
        case 0x4B:
            // 0x4B type argument for generic method in method reference 
            // expression using ::Identifier type_argument_target
            type_annotation_pt[j].target_info.type_argument_target.offset = read_u2(file);
            type_annotation_pt[j].target_info.type_argument_target.type_argument_index = read_u1(file);
        break;
        default:
            printf("[ERROR] Invalid target type inside attribute type annotations!");
            break;
        }
        type_annotation_pt[j].target_path.path_length = read_u1(file);
        type_annotation_pt[j].target_path.path = calloc(
            type_annotation_pt[j].target_path.path_length,
            sizeof (vm_type_path_t)
        );
        for(uint16_t k = 0; k < (type_annotation_pt[j].target_path.path_length); k++)
        {
            type_annotation_pt[j].target_path.path[k].type_path_kind = read_u1(file);
            type_annotation_pt[j].target_path.path[k].type_argument_index = read_u1(file);
        }
    }
}

/**
 * @brief A function dedicated to filling the attributes field of the
 * vm_class_file_t structure.
 * @param attributes_count
 * @param attributes
 * @param constant_pool
 * @param file A file_t pointer that has the .class loaded.
 */
void attributes_parser(uint16_t attributes_count, vm_attribute_info_t *attributes, vm_cp_info_t *constant_pool, file_t *file) {
    vm_utf8_t utf8;

    for (int i = 0; i < (attributes_count); i++) {
        attributes[i].attribute_name_index = read_u2(file);
        attributes[i].attribute_length = read_u4(file);

        utf8 = constant_pool[attributes[i].attribute_name_index].info.utf8_info;

        switch (attribute_name_to_int(utf8.length, utf8.bytes)) {
        case ConstantValue:
            attributes[i].info.constantvalue_attribute.constantvalue_index = read_u2(file);
            break;

        case Code:
            attributes[i].info.code_attribute.max_stack = read_u2(file);
            attributes[i].info.code_attribute.max_local = read_u2(file);
            attributes[i].info.code_attribute.code_length = read_u4(file);
            attributes[i].info.code_attribute.code = calloc(
                attributes[i].info.code_attribute.code_length,
                sizeof (uint8_t));

            for (int j = 0; j < (attributes[i].info.code_attribute.code_length); j++) {
                attributes[i].info.code_attribute.code[j] = read_u1(file);
            }

            attributes[i].info.code_attribute.exception_table_length = read_u2(file);
            attributes[i].info.code_attribute.exception_table = calloc(
                attributes[i].info.code_attribute.exception_table_length,
                sizeof (vm_exception_table_t));

            for (int j = 0; j < (attributes[i].info.code_attribute.exception_table_length); j++) {
                attributes[i].info.code_attribute.exception_table[j].start_pc = read_u2(file);
                attributes[i].info.code_attribute.exception_table[j].end_pc = read_u2(file);
                attributes[i].info.code_attribute.exception_table[j].handler_pc = read_u2(file);
                attributes[i].info.code_attribute.exception_table[j].catch_type = read_u2(file);
            }

            attributes[i].info.code_attribute.attributes_count = read_u2(file);
            attributes[i].info.code_attribute.attributes = calloc(
                attributes[i].info.code_attribute.attributes_count,
                sizeof (vm_attribute_info_t));

            attributes_parser(attributes[i].info.code_attribute.attributes_count,
                attributes[i].info.code_attribute.attributes, constant_pool, file);
            break;

        case StackMapTable:
            attributes[i].info.stackmaptable_attribute.number_of_entries = read_u2(file);
            attributes[i].info.stackmaptable_attribute.entries = calloc(
                attributes[i].info.stackmaptable_attribute.number_of_entries,
                sizeof (vm_stack_map_frame_t));

            stack_map_table_parser(&attributes[i].info.stackmaptable_attribute, file);
            break;

        case Exceptions:
            attributes[i].info.exceptions_attribute.number_of_exceptions = read_u2(file);
            attributes[i].info.exceptions_attribute.exception_index_table = calloc(
                attributes[i].info.exceptions_attribute.number_of_exceptions,
                sizeof (uint16_t));

            for (int j = 0; j < (attributes[i].info.exceptions_attribute.number_of_exceptions); j++) {
                attributes[i].info.exceptions_attribute.exception_index_table[j] = read_u2(file);
            }
            break;

        case InnerClasses:
            attributes[i].info.innerclasses_attribute.number_of_classes = read_u2(file);
            attributes[i].info.innerclasses_attribute.classes = calloc(
                attributes[i].info.innerclasses_attribute.number_of_classes,
                sizeof (vm_classes_t));

            for (int j = 0; j < (attributes[i].info.innerclasses_attribute.number_of_classes); j++) {
                attributes[i].info.innerclasses_attribute.classes[j].inner_class_info_index = read_u2(file);
                attributes[i].info.innerclasses_attribute.classes[j].outer_class_info_index = read_u2(file);
                attributes[i].info.innerclasses_attribute.classes[j].inner_name_index = read_u2(file);
                attributes[i].info.innerclasses_attribute.classes[j].inner_class_access_flags = read_u2(file);
            }
            break;

        case EnclosingMethod:
            attributes[i].info.enclosingmethod_attribute.class_index = read_u2(file);
            attributes[i].info.enclosingmethod_attribute.method_index = read_u2(file);
            break;

        case Synthetic:
            /* Empty */
            break;

        case Signature:
            attributes[i].info.signature_attribute.signature_index = read_u2(file);
            break;

        case SourceFile:
            attributes[i].info.sourcefile_attribute.sourcefile_index = read_u2(file);
            break;

        case SourceDebugExtension:
            attributes[i].info.sourcedebugextension_attribute.debug_extension = calloc(
                attributes[i].attribute_length, sizeof (uint8_t));

            for (int j = 0; j < (attributes[i].attribute_length); j++) {
                attributes[i].info.sourcedebugextension_attribute.debug_extension[j] = read_u1(file);
            }
            break;

        case LineNumberTable:
            attributes[i].info.linenumbertable_attribute.line_number_table_length = read_u2(file);
            attributes[i].info.linenumbertable_attribute.line_number_table = calloc(
                attributes[i].info.linenumbertable_attribute.line_number_table_length,
                sizeof (vm_line_number_t));

            for (int j = 0; j < (attributes[i].info.linenumbertable_attribute.line_number_table_length); j++) {
                attributes[i].info.linenumbertable_attribute.line_number_table[j].start_pc = read_u2(file);
                attributes[i].info.linenumbertable_attribute.line_number_table[j].line_number = read_u2(file);
            }
            break;

        case LocalVariableTable:
            attributes[i].info.localvariabletable_attribute.local_variable_table_length = read_u2(file);
            attributes[i].info.localvariabletable_attribute.local_variable_table = calloc(
                attributes[i].info.localvariabletable_attribute.local_variable_table_length,
                sizeof (vm_local_variable_t));

            for (int j = 0; j < (attributes[i].info.localvariabletable_attribute.local_variable_table_length); j++) {
                attributes[i].info.localvariabletable_attribute.local_variable_table[j].start_pc = read_u2(file);
                attributes[i].info.localvariabletable_attribute.local_variable_table[j].length = read_u2(file);
                attributes[i].info.localvariabletable_attribute.local_variable_table[j].name_index = read_u2(file);
                attributes[i].info.localvariabletable_attribute.local_variable_table[j].descriptor_index = read_u2(file);
                attributes[i].info.localvariabletable_attribute.local_variable_table[j].index = read_u2(file);
            }
            break;

        case LocalVariableTypeTable:
            attributes[i].info.localvariabletypetable_attribute.local_variable_type_table_length = read_u2(file);
            attributes[i].info.localvariabletypetable_attribute.local_variable_type_table = calloc(
                attributes[i].info.localvariabletypetable_attribute.local_variable_type_table_length,
                sizeof (vm_local_variable_type_t));

            for (int j = 0; j < (attributes[i].info.localvariabletypetable_attribute.local_variable_type_table_length); j++) {
                attributes[i].info.localvariabletypetable_attribute.local_variable_type_table[j].start_pc = read_u2(file);
                attributes[i].info.localvariabletypetable_attribute.local_variable_type_table[j].length = read_u2(file);
                attributes[i].info.localvariabletypetable_attribute.local_variable_type_table[j].name_index = read_u2(file);
                attributes[i].info.localvariabletypetable_attribute.local_variable_type_table[j].signature_index = read_u2(file);
                attributes[i].info.localvariabletypetable_attribute.local_variable_type_table[j].index = read_u2(file);
            }
            break;

        case Deprecated:
            /* Empty */
            break;

        case RuntimeVisibleAnnotations:
            attributes[i].info.runtimevisibleannotations_attribute.num_annotations = read_u2(file);
            attributes[i].info.runtimevisibleannotations_attribute.annotations = calloc(
                attributes[i].info.runtimevisibleannotations_attribute.num_annotations,
                sizeof (vm_annotation_t));

            for (int j = 0; j < (attributes[i].info.runtimevisibleannotations_attribute.num_annotations); j++)
            {
                attributes[i].info.runtimevisibleannotations_attribute.annotations[j].type_index = read_u2(file);
                attributes[i].info.runtimevisibleannotations_attribute.annotations[j].num_element_value_pairs = read_u2(file);
                attributes[i].info.runtimevisibleannotations_attribute.annotations[j].element_value_pairs = calloc(
                    attributes[i].info.runtimevisibleannotations_attribute.annotations[j].num_element_value_pairs,
                    sizeof (vm_element_value_pairs_t)
                );
                element_value_pairs_parser(
                    attributes[i].info.runtimevisibleannotations_attribute.annotations[j].num_element_value_pairs,
                    attributes[i].info.runtimevisibleannotations_attribute.annotations[j].element_value_pairs,
                    file);
            }
            break;

        case RuntimeInvisibleAnnotations:
        attributes[i].info.runtimeinvisibleannotations_attribute.num_annotations = read_u2(file);
            attributes[i].info.runtimeinvisibleannotations_attribute.annotations = calloc(
                attributes[i].info.runtimeinvisibleannotations_attribute.num_annotations,
                sizeof (vm_annotation_t));

            for (int j = 0; j < (attributes[i].info.runtimeinvisibleannotations_attribute.num_annotations); j++)
            {
                attributes[i].info.runtimeinvisibleannotations_attribute.annotations[j].type_index = read_u2(file);
                attributes[i].info.runtimeinvisibleannotations_attribute.annotations[j].num_element_value_pairs = read_u2(file);
                attributes[i].info.runtimeinvisibleannotations_attribute.annotations[j].element_value_pairs = calloc(
                    attributes[i].info.runtimeinvisibleannotations_attribute.annotations[j].num_element_value_pairs,
                    sizeof (vm_element_value_pairs_t)
                );
                element_value_pairs_parser(
                    attributes[i].info.runtimeinvisibleannotations_attribute.annotations[j].num_element_value_pairs,
                    attributes[i].info.runtimeinvisibleannotations_attribute.annotations[j].element_value_pairs,
                    file);
            }
            break;

        case RuntimeVisibleParameterAnnotations:
            attributes[i].info.runtimevisibleparameterannotations_attribute.num_parameters = read_u1(file);
            attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations = calloc(
                attributes[i].info.runtimevisibleparameterannotations_attribute.num_parameters,
                sizeof (vm_parameter_annotations_t));

            for (int j = 0; j < (attributes[i].info.runtimevisibleparameterannotations_attribute.num_parameters); j++)
            {
                attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].num_annotations = read_u2(file);
                attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].annotations = calloc(
                    attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].num_annotations,
                    sizeof (vm_annotation_t)
                );
                for (int k = 0; k < (attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].num_annotations); k++)
                {
                    attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].type_index = read_u2(file);
                    attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].num_element_value_pairs = read_u2(file);
                    attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].element_value_pairs = calloc(
                        attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].num_element_value_pairs,
                        sizeof (vm_element_value_pairs_t)
                    );
                    element_value_pairs_parser(
                        attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].num_element_value_pairs,
                        attributes[i].info.runtimevisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].element_value_pairs,
                        file);
                }
            }
            break;

        case RuntimeInvisibleParameterAnnotations:
            attributes[i].info.runtimeinvisibleparameterannotations_attribute.num_parameters = read_u1(file);
            attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations = calloc(
                attributes[i].info.runtimeinvisibleparameterannotations_attribute.num_parameters,
                sizeof (vm_parameter_annotations_t));
            for (int j = 0; j < (attributes[i].info.runtimeinvisibleparameterannotations_attribute.num_parameters); j++)
            {
                attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].num_annotations = read_u2(file);
                attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].annotations = calloc(
                    attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].num_annotations,
                    sizeof (vm_annotation_t)
                );
                for (int k = 0; k < (attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].num_annotations); k++)
                {
                    attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].type_index = read_u2(file);
                    attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].num_element_value_pairs = read_u2(file);
                    attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].element_value_pairs = calloc(
                        attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].num_element_value_pairs,
                        sizeof (vm_element_value_pairs_t)
                    );
                    element_value_pairs_parser(
                        attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].num_element_value_pairs,
                        attributes[i].info.runtimeinvisibleparameterannotations_attribute.parameter_annotations[j].annotations[k].element_value_pairs,
                        file);
                }
            }
            break;

        case RuntimeVisibleTypeAnnotations:
            attributes[i].info.runtimevisibletypeannotations_attribute.num_annotations = read_u2(file);
            attributes[i].info.runtimevisibletypeannotations_attribute.annotations = calloc(
                attributes[i].info.runtimevisibletypeannotations_attribute.num_annotations,
                sizeof (vm_type_annotation_t));
            type_annotations_parser(
                        attributes[i].info.runtimevisibletypeannotations_attribute.num_annotations,
                        attributes[i].info.runtimevisibletypeannotations_attribute.annotations,
                        file);
            break;

        case RuntimeInvisibleTypeAnnotations:
            attributes[i].info.runtimeinvisibletypeannotations_attribute.num_annotations = read_u2(file);
            attributes[i].info.runtimeinvisibletypeannotations_attribute.annotations = calloc(
                attributes[i].info.runtimeinvisibletypeannotations_attribute.num_annotations,
                sizeof (vm_type_annotation_t));
            type_annotations_parser(
                        attributes[i].info.runtimeinvisibletypeannotations_attribute.num_annotations,
                        attributes[i].info.runtimeinvisibletypeannotations_attribute.annotations,
                        file);
            break;

        case AnnotationDefault:
            // TO DO: VALIDAR SE ESSA ESTRUTURA ESTÁ IMPLEMENTADA CORRETAMENTE.
            break;

        case BootstrapMethods:
            attributes[i].info.bootstrapmethods_attribute.num_bootstrap_methods = read_u2(file);
            attributes[i].info.bootstrapmethods_attribute.bootstrap_methods_table = calloc(
                attributes[i].info.bootstrapmethods_attribute.num_bootstrap_methods,
                sizeof (vm_bootstrap_methods_table_t)
            );
            for(uint16_t j = 0; j < (attributes[i].info.bootstrapmethods_attribute.num_bootstrap_methods); j++)
            {
                attributes[i].info.bootstrapmethods_attribute.bootstrap_methods_table[j].bootstrap_method_ref = read_u2(file);
                attributes[i].info.bootstrapmethods_attribute.bootstrap_methods_table[j].num_bootstrap_arguments = read_u2(file);
                attributes[i].info.bootstrapmethods_attribute.bootstrap_methods_table[j].bootstrap_arguments = calloc(
                    attributes[i].info.bootstrapmethods_attribute.bootstrap_methods_table[j].num_bootstrap_arguments,
                    sizeof (uint16_t)
                );
                for(uint16_t k = 0; k < (attributes[i].info.bootstrapmethods_attribute.bootstrap_methods_table[j].num_bootstrap_arguments); k++)
                {
                    attributes[i].info.bootstrapmethods_attribute.bootstrap_methods_table[j].bootstrap_arguments[k] = read_u2(file);
                }
            }
            break;

        case MethodParameters:
            attributes[i].info.methodparameters_attribute.parameters_count = read_u1(file);
            attributes[i].info.methodparameters_attribute.parameters = calloc(
                attributes[i].info.methodparameters_attribute.parameters_count,
                sizeof (vm_parameters_array_t)
            );
            for(uint16_t j = 0; j < (attributes[i].info.methodparameters_attribute.parameters_count); j++)
            {
                attributes[i].info.methodparameters_attribute.parameters[j].name_index = read_u2(file);
                attributes[i].info.methodparameters_attribute.parameters[j].access_flags = read_u2(file);
            }
            break;

        default:
            break;
        }
    }
}

/**
 * @brief A function dedicated to filling the fields field of the
 * vm_class_file_t structure.
 * @param file A file_t pointer that has the .class loaded.
 * @param cf A pointer to a vm_class_file_t structure.
 */
void fields_parser(file_t *file, vm_class_file_t *cf) {
    for (int i = 0; i < (cf->fields_count); i++) {
        cf->fields[i].access_flags = read_u2(file);
        cf->fields[i].name_index = read_u2(file);
        cf->fields[i].descriptor_index = read_u2(file);
        cf->fields[i].attributes_count = read_u2(file);
        cf->fields[i].attributes = calloc(cf->fields[i].attributes_count,
            sizeof (vm_attribute_info_t));

        attributes_parser(cf->fields[i].attributes_count, cf->fields[i].attributes, cf->constant_pool, file);
    }
}

/**
 * @brief Parses the .class bytecode to a ClassFile structure.
 * @param file A FILE (from stdio, in rb mode) pointer to a .class file.
 * @param cf A pointer to a ClassFile structure.
 * @returns A ClassFile structure containing the .class information.
 */
const char * class_file_parser(file_t *file, vm_class_file_t *cf) {
    cf->magic = read_u4(file);
    cf->minor_version = read_u2(file);
    cf->major_version = read_u2(file);

    cf->constant_pool_count = read_u2(file);
    cf->constant_pool = calloc(cf->constant_pool_count - 1, sizeof (vm_cp_info_t));

    constant_pool_parser(file, cf);

    cf->access_flags = read_u2(file);
    cf->this_class = read_u2(file);
    cf->super_class = read_u2(file);

    cf->interfaces_count = read_u2(file);
    cf->interfaces = calloc(cf->interfaces_count, sizeof (uint16_t));

    interfaces_parser(file, cf);

    cf->fields_count = read_u2(file);
    cf->fields = calloc(cf->fields_count, sizeof (vm_field_info_t));

    fields_parser(file, cf);
}

/**
 * @brief Prints the information contained in the ClassFile structure in a
 * formatted manner.
 * @param class_file A ClassFile structure to be printed.
 */
void class_file_reader(vm_class_file_t class_file, file_t *file) {

    uint16_t cp_size = class_file.constant_pool_count;

    // gets the jvm execution target
    const char *java_version = vm_target(class_file.major_version);

    printf("\n");
    printf("%s\n\n", file->filename);
    printf("%2sMAGIC:                %10X\n", "", class_file.magic);
    printf("%2sMAJOR VERSION:        %10d\n", "", class_file.major_version);
    printf("%2sMINOR VERSION:        %10d\n", "", class_file.minor_version);
    printf("%2sJAVA TARGET:          %10s\n", "", java_version);
    printf("%2sCONSTANT POOL COUNT:  %10d\n", "", cp_size);
    printf("\n");

    printf("CONSTANT POOL\n");
    printf("-------------\n\n");

    for (uint16_t i = 0; i < (class_file.constant_pool_count - 1); i++) {

        vm_cp_info_t cp_info = class_file.constant_pool[i];

        printf("%3s #%d\t| %3d %3s %-10s", "", i+1, cp_info.tag,
            tag_constants[cp_info.tag], "");

        switch (class_file.constant_pool[i].tag) {
        case CONSTANT_Class:
            printf("\t| name_index: %5d", cp_info.info.class_info.name_index);
            printf("\t|\n");
            break;

        case CONSTANT_Fieldref:
            printf("\t| class_index: %5d",
                cp_info.info.fieldref_info.class_index);
            printf("\t| name_and_type_index: %5d\n",
                cp_info.info.fieldref_info.name_and_type_index);
            break;

        case CONSTANT_Methodref:
            printf("\t| class_index:  % 5d",
                cp_info.info.methodref_info.class_index);
            printf("\t| name_and_type_index: % 5d\n",
                cp_info.info.methodref_info.name_and_type_index);
            break;

        case CONSTANT_InterfaceMethodref:
            printf("\t| class_index:  % 5d",
                cp_info.info.interfacemethodref_info.class_index);
            printf("\t| name_and_type_index: % 5d\n",
                cp_info.info.interfacemethodref_info.name_and_type_index);
            break;

        case CONSTANT_String:
            printf("\t| string_index: % 5d",
                cp_info.info.string_info.string_index);
            printf("\t|\n");
            break;

        case CONSTANT_Integer:
            {
                uint32_t b = cp_info.info.integer_info.bytes;
                int number = (int)b;

                printf("\t| %d (%04X)\n", number, b);
            }
            break;

        case CONSTANT_Float:
            {
                uint32_t bytes = cp_info.info.float_info.bytes;
                float number = vm_itof(bytes);

                printf("\t| %f (%4X)\n", number, bytes);
            }
            break;

        case CONSTANT_Long:
            {
                vm_class_file_t cf = class_file;

                uint32_t high = cf.constant_pool[i].info.long_info.high_bytes;
                uint32_t low = cf.constant_pool[i].info.long_info.low_bytes;

                long number = vm_itolf(low, high);

                printf("\t| %ld (%4X) (%4X)\n", number, low, high);
            }
            break;

        case CONSTANT_Double:
            {
                vm_class_file_t cf = class_file;

                uint32_t high = cf.constant_pool[i].info.double_info.high_bytes;
                uint32_t low = cf.constant_pool[i].info.double_info.low_bytes;

                double number = vm_itod(low, high);

                printf("\t| %lf (%4X) (%4X)\n", number, low, high);
            }
            break;

        case CONSTANT_NameAndType:
            printf("\t| name_index: %-5d",
                cp_info.info.nameandtype_info.name_index);
            printf("\t| descriptor_index: %-5d\n",
                cp_info.info.nameandtype_info.descriptor_index);
            break;

        case CONSTANT_Utf8:
            {
                uint16_t length = cp_info.info.utf8_info.length;
                uint8_t *bytes = cp_info.info.utf8_info.bytes;

                uint16_t *heap = vm_utf8_to_uint16_t(length, bytes);

                printf("\t| \"");
                for (int j = 0; j < cp_info.info.utf8_info.length; j++) {
                    printf("%lc", heap[j]);
                }
                printf("\"\n");
                break;
            }

        case CONSTANT_MethodHandle:
            printf("\t|MethodHandle - Ignoring");
            printf("\t|\n");
            break;

        case CONSTANT_MethodType:
            printf("\t|MethodType - Ignoring");
            printf("\t|\n");
            break;

        case CONSTANT_InvokeDynamic:
            printf("\t|InvokeDynamic - Ignoring");
            printf("\t|\n");
            break;

        default:
            printf("\n");
            break;
        }
    }
}

void vm_load_constant_pool(file_t *file) {
    vm_class_file_t class_file;

    file->read = 0;

    vm_init_tag_map();

    class_file_parser(file, &class_file);
    class_file_reader(class_file, file);
}
