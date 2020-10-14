#include "vm_constant_pool.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#include "vm_file.h"

#define CONSTANT_Class (0x07)
#define CONSTANT_Fieldref (0x09)
#define CONSTANT_Methodref (0x0A)
#define CONSTANT_InterfaceMethodref (0x0B)
#define CONSTANT_String (0x08)
#define CONSTANT_Integer (0x03)
#define CONSTANT_Float (0x04)
#define CONSTANT_Long (0x05)
#define CONSTANT_Double (0x06)
#define CONSTANT_NameAndType (0x0C)
#define CONSTANT_Utf8 (0x01)
#define CONSTANT_MethodHandle (0x0F)
#define CONSTANT_MethodType (0x10)
#define CONSTANT_InvokeDynamic (0x12)

typedef unsigned int u4;
typedef unsigned short u2;
typedef unsigned char u1;

const u4 MAGIC[4] = {0xCA, 0xFE, 0xBA, 0xBE};

u1 read_u1(FILE * file)
{
    u1 value = fgetc(file);

    return value;
}

u2 read_u2(FILE * file)
{
    u2 value = read_u1(file);

    value = value << 8;
    value = value | read_u1(file);

    return value;
}

u4 read_u4(FILE * file)
{
    u4 value = read_u1(file);

    for (int i = 0; i < 3; i++)
    {
        value = value << 8;
        value = value | read_u1(file);
    }

    return value;
}

/**
 * @brief Class_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef struct Class
{
    u2 name_index;
} Class;

/**
 * @brief Fieldref_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef struct Fieldref
{
    u2 class_index;
    u2 name_and_type_index;
} Fieldref;

/**
 * @brief Methodref_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef Fieldref Methodref;

/**
 * @brief InterfaceMethodref_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef Fieldref InterfaceMethodref;

/**
 * @brief String_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef struct String
{
    u2 string_index;
} String;

/**
 * @brief Integer_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef struct Integer
{
    u4 bytes;
} Integer;

/**
 * @brief Float_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef Integer Float;

/**
 * @brief Long_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef struct Long
{
    u4 high_bytes;
    u4 low_bytes;
} Long;

/**
 * @brief Double_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef Long Double;

/**
 * @brief NameAndType_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef struct NameAndType
{
    u2 name_index;
    u2 descriptor_index;
} NameAndType;

/**
 * @brief Utf8_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef struct Utf8
{
    u2 length;
    u1 * bytes;
} Utf8;

/**
 * @brief A union of all the info structures implemented in this project.
 */
typedef union info
{
    Class class_info;
    Fieldref fieldref_info;
    Methodref methodref_info;
    InterfaceMethodref interfacemethodref_info;
    String string_info;
    Integer integer_info;
    Float float_info;
    Long long_info;
    Double double_info;
    NameAndType nameandtype_info;
    Utf8 utf8_info;
} info;

/**
 * @brief cp_info structure as defined in The Java Virtual Machine
 * Specification (Java SE 8 edition).
 */
typedef struct cp_info
{
    u1 tag;
    info info;
} cp_info;

/**
 * @brief A ClassFile structure representing a single .class file as defined in
 * The Java Virtual Machine Specification (Java SE 8 edition).
 */
typedef struct ClassFile
{
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info * constant_pool;
    //u2 access_flags;
    //u2 this_class;
    //u2 super_class;
    //u2 interfaces_count;
    //u2 * interfaces;
    //u2 fields_count;
    //field_info * fields;
    //u2 methods_count;
    //method_info * methods;
    //u2 attributes_count;
    //attribute_info * attributes;
} ClassFile;

const char * SUCCESS = "Success!";
const char * EOF_ERROR = "[ERROR] eof reached";
const char * FSEEK_ERROR = "[ERROR] fseek failed to reposition the stream";

/**
 * @brief Searches the bytecode of a .class file looking for the 0xCAFEBABE
 * number.
 * @param file A FILE (from stdio, in rb mode) pointer to a .class file.
 * @returns A string containing either a error message or 'Success!'.
 */
const char * find_magic(FILE * file)
{
    u1 byte;

    for (u1 i = 0; i < 4; i++)
    {
        byte = read_u1(file);

        // End of File reached
        if (feof(file))
            return EOF_ERROR;

        // Checks if read byte is one of the magic bytes.
        // On a positive match it continues the loop until MAGIC[] ends.
        if (byte == MAGIC[i])
        {
            continue;
        }
        // On a negative match it moves the file stream to the byte following
        // the first positive match of the current streak.
        else if (fseek(file, -i, SEEK_CUR))
        {
            // fseek returns non-zero on error
            return FSEEK_ERROR;
        }
        // If fseek succeeded in moving the stream, changes the index to zero.
        else
        {
            // The for statement will increment it to zero.
            i = -1;
        }
    }

    return SUCCESS;
}

/**
 * @brief A function dedicated to filling the constant_pool field of the
 * ClassFile structure.
 * @param file A FILE (from stdio, in rb mode) pointer to a .class file.
 * @param cf A pointer to a ClassFile structure.
 * @returns void
 */
const char * constant_pool_parser(FILE * file, ClassFile * cf)
{
    u1 tag;

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
            cf->constant_pool[i].tag = tag;
            cf->constant_pool[i].info.utf8_info.length = read_u2(file);
            cf->constant_pool[i].info.utf8_info.bytes = (u1*) calloc(cf->constant_pool[i].info.utf8_info.length, sizeof(u1));
            for(int j = 0; j < cf->constant_pool[i].info.utf8_info.length; j++)
                cf->constant_pool[i].info.utf8_info.bytes[j] = read_u1(file);
            break;

        case CONSTANT_MethodHandle:
            if (fseek(file, 3, SEEK_CUR))
            {
                // fseek returns non-zero on error
                return FSEEK_ERROR;
            }
            break;

        case CONSTANT_MethodType:
            if (fseek(file, 2, SEEK_CUR))
            {
                // fseek returns non-zero on error
                return FSEEK_ERROR;
            }
            break;

        case CONSTANT_InvokeDynamic:
            if (fseek(file, 4, SEEK_CUR))
            {
                // fseek returns non-zero on error
                return FSEEK_ERROR;
            }
            break;

        default:
            break;
        }
    }

    return SUCCESS;
}

/**
 * @brief Parses the .class bytecode to a ClassFile structure.
 * @param file A FILE (from stdio, in rb mode) pointer to a .class file.
 * @param cf A pointer to a ClassFile structure.
 * @returns A ClassFile structure containing the .class information.
 */
const char * class_file_parser(FILE * file, ClassFile * cf)
{
    if (fseek(file, -4, SEEK_CUR))
    {
        // fseek returns non-zero on error
        return FSEEK_ERROR;
    }
    else
    {
        cf->magic = read_u4(file);
        cf->minor_version = read_u2(file);
        cf->major_version = read_u2(file);
        cf->constant_pool_count = read_u2(file);
        cf->constant_pool = (cp_info *) malloc(
            sizeof(cp_info) * (cf->constant_pool_count - 1));
    }

    return constant_pool_parser(file, cf);
}

u2 * system_out_println(ClassFile * cf, u2 table_index)
{
    u2 length = cf->constant_pool[table_index].info.utf8_info.length;
    u1 * b = cf->constant_pool[table_index].info.utf8_info.bytes;
    u2 * heap = NULL;

    for (int i = 0; i < length; i++) {
        heap = realloc(heap, (sizeof(u2) * (i+1)));

        if (b[i] >> 7) {
            if ((b[i] >> 5) & (0x01)) {
                if (b[i] == 0xED) { // Characters with code points above U+FFFF
                    heap[i] = 0x0000;
                } else { // '\u0800' to '\uFFFF'
                    heap[i] = (((b[i] & 0x0F) << 12) | ((b[i+1] & 0x3F) << 6) | (b[i+2] & 0x3F));
                }
            } else { // '\u0080' up to '\u07FF' and '\u0000'
                heap[i] = (((b[i] & 0x1F) << 6) | (b[i+1] & 0x3F));
            }
        } else { // '\u0001' up to '\u007F'
            heap[i] = b[i];
        }
    }

    return heap;
}

/**
 * @brief Prints the information contained in the ClassFile structure in a
 * formatted manner.
 * @param class_file A ClassFile structure to be printed.
 */
void class_file_reader(ClassFile class_file, file_t *file)
{
    const char* java_version = "";

    switch (class_file.major_version) {
    case 45:
        java_version = "1.1";
        break;
    case 46:
        java_version = "1.2";
        break;
    case 47:
        java_version = "1.3";
        break;
    case 48:
        java_version = "1.4";
        break;
    }

    printf("\n");
    printf("%s\n{\n", file->filename);
    printf("\tMAGIC:\t\t\t   0x%04X\n", class_file.magic);
    printf("\tMAJOR VERSION:\t\t        % 5d\n", class_file.major_version);
    printf("\tMINOR VERSION:\t\t        % 5d \n", class_file.minor_version);
    printf("\tJAVA TARGET:\t\t          % s\n", java_version);
    printf("\tCONSTANT POOL COUNT:\t        % 5d\n",
    class_file.constant_pool_count);
    printf("}\n\n");

    printf("Constant Pool\n{\n");

    for (int i = 0; i < (class_file.constant_pool_count - 1); i++)
    {
        printf("\t|index: % 5d\t|tag: % 3d", i+1, class_file.constant_pool[i].tag);

        switch (class_file.constant_pool[i].tag)
        {
        case CONSTANT_Class:
            printf("\t|name_index:   % 5d", class_file.constant_pool[i].info.class_info.name_index);
            printf("\t|\n");
            break;

        case CONSTANT_Fieldref:
            printf("\t|class_index:  % 5d", class_file.constant_pool[i].info.fieldref_info.class_index);
            printf("\t|name_and_type_index: % 5d\n", class_file.constant_pool[i].info.fieldref_info.name_and_type_index);
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
            printf("\t|bytes: %04X", class_file.constant_pool[i].info.float_info.bytes);
            printf("\t|\n");
            break;

        case CONSTANT_Long:
            printf("\t|bytes: %04X\t", class_file.constant_pool[i].info.long_info.high_bytes);
            printf("\t|bytes: %04X\n", class_file.constant_pool[i].info.long_info.low_bytes);
            break;

        case CONSTANT_Double:
            printf("\t|bytes: %04X\t", class_file.constant_pool[i].info.double_info.high_bytes);
            printf("\t|bytes: %04X\n", class_file.constant_pool[i].info.double_info.low_bytes);
            break;

        case CONSTANT_NameAndType:
            printf("\t|name_index:   % 5d", class_file.constant_pool[i].info.nameandtype_info.name_index);
            printf("\t|descriptor_index:    % 5d\n", class_file.constant_pool[i].info.nameandtype_info.descriptor_index);
            break;

        case CONSTANT_Utf8:
            {
                printf("\t|length:       % 5d", class_file.constant_pool[i].info.utf8_info.length);
                u2 * heap = system_out_println(&class_file, i);
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

    printf("}\n\n");
}

void vm_load_constant_pool(file_t *file)
{
    FILE *fd;

    const char * output;
    ClassFile class_file;

    fd = fopen(file->filename, "rb");

    fseek(fd, 0, SEEK_SET);

    find_magic(fd);
    class_file_parser(fd, &class_file);

    fclose(fd);

    class_file_reader(class_file, file);
}