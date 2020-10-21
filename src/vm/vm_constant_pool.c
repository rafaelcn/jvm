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
void constant_pool_parser(file_t *file, vm_class_file_t *cf)
{
    uint8_t tag;

    for (int i = 0; i < (cf->constant_pool_count - 1); i++)
    {
        tag = read_u1(file);

        switch (tag)
        {
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
            {
                cf->constant_pool[i].tag = tag;
                cf->constant_pool[i].info.utf8_info.length = read_u2(file);
                cf->constant_pool[i].info.utf8_info.bytes = (uint8_t*) calloc(
                    cf->constant_pool[i].info.utf8_info.length, sizeof(uint8_t));

                uint16_t size = cf->constant_pool[i].info.utf8_info.length;

                for(int j = 0; j < size; j++) {
                    cf->constant_pool[i].info.utf8_info.bytes[j] = read_u1(file);
                }
            }
            break;

        case CONSTANT_MethodHandle:

            break;

        case CONSTANT_MethodType:

            break;

        case CONSTANT_InvokeDynamic:

            break;

        default:
            break;
        }
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
    cf->constant_pool = calloc(cf->constant_pool_count - 1,
                               sizeof (vm_cp_info_t));

    constant_pool_parser(file, cf);
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

        printf("%3s #%d\t| %3d %3s %-15s", "", i+1,
               class_file.constant_pool[i].tag,
               tag_constants[class_file.constant_pool[i].tag], "");

        switch (class_file.constant_pool[i].tag) {
        case CONSTANT_Class:
            printf("\t|name_index:   %5d", class_file.constant_pool[i].info.class_info.name_index);
            printf("\t|\n");
            break;

        case CONSTANT_Fieldref:
            printf("\t|class_index:  %5d", class_file.constant_pool[i].info.fieldref_info.class_index);
            printf("\t|name_and_type_index: %5d\n", class_file.constant_pool[i].info.fieldref_info.name_and_type_index);
            break;

        case CONSTANT_Methodref:
            printf("\t|class_index:  % 5d", class_file.constant_pool[i].info.methodref_info.class_index);
            printf("\t|name_and_type_index: % 5d\n", class_file.constant_pool[i].info.methodref_info.name_and_type_index);
            break;

        case CONSTANT_InterfaceMethodref:
            printf("\t|class_index:  % 5d", class_file.constant_pool[i].info.interfacemethodref_info.class_index);
            printf("\t|name_and_type_index: % 5d\n", class_file.constant_pool[i].info.interfacemethodref_info.name_and_type_index);
            break;

        case CONSTANT_String:
            printf("\t|string_index: % 5d", class_file.constant_pool[i].info.string_info.string_index);
            printf("\t|\n");
            break;

        case CONSTANT_Integer:
            printf("\t|bytes: %04X", class_file.constant_pool[i].info.integer_info.bytes);
            printf("\t|\n");
            break;

        case CONSTANT_Float:
            {
                vm_class_file_t cf = class_file;

                uint32_t bytes = cf.constant_pool[i].info.float_info.bytes;
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
            printf("\t|name_index: %5d", class_file.constant_pool[i].info.nameandtype_info.name_index);
            printf("\t|descriptor_index:    % 5d\n", class_file.constant_pool[i].info.nameandtype_info.descriptor_index);
            break;

        case CONSTANT_Utf8:
            {
                //printf("\t|length: %5d", class_file.constant_pool[i].info.utf8_info.length);

                uint16_t length = class_file.constant_pool[i].info.utf8_info.length;
                uint8_t *b = class_file.constant_pool[i].info.utf8_info.bytes;

                uint16_t *heap = vm_utf8_to_uint16_t(length, b);

                printf("\t|\"");
                for (int j = 0; j < class_file.constant_pool[i].info.utf8_info.length; j++) {
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
            break;
        }
    }
}

void vm_load_constant_pool(file_t *file)
{
    vm_class_file_t class_file;

    file->read = 0;

    vm_init_tag_map();

    class_file_parser(file, &class_file);
    class_file_reader(class_file, file);
}
