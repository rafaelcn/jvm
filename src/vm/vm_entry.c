#include "vm_entry.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "vm_settings.h"
#include "vm_constant_pool.h"

#include "lib/vm_string.h"

#include "utils/vm_errors.h"
#include "utils/vm_logger.h"
#include "utils/vm_checks.h"


int vm_init(const char* filename, file_t *file) {
    FILE *fd = fopen(filename, "rb");

    if (!vm_valid_pointer((void*) fd)) {
        char buffer[512];
        sprintf(buffer, "failed to read filename %s", filename);

        vm_log(stdout, buffer, __LINE__, __FILE__,
            VM_LOG_WARNING);
        return 1;
    }

    file->filename = filename;
    file->read = 0;

    // getting the size of the file
    fseek(fd, 0, SEEK_END);

    file->size = ftell(fd);

    fseek(fd, 0, SEEK_SET);

    // create the file buffer
    char* buffer = calloc(file->size+1, sizeof(char *));
    file->data = buffer;

    fread(buffer, sizeof(char *), file->size, fd);
    fclose(fd);

    buffer[file->size] = '\0';

    if (__debug_t) {
        for(size_t i = 0; i < file->size; i++) {
            printf("%.2X ", file->data[i]);
            file->read++;
        }

        printf("\n\n%ld in bytes size, %ld bytes read.\n", file->size,
               file->read);
    }

    // reset read information to future use
    file->read = 0;

    return 0;
}

void vm_inform(file_t *file) {
    vm_class_file_t class_file;

    file->read = 0;

    vm_init_tag_map();

    class_file_parser(file, &class_file);

    // inform
    class_file_reader(class_file, file);
}

const char * vm_execute(file_t *file) {
    vm_class_file_t class_file;

    file->read = 0;

    vm_init_tag_map();

    class_file_parser(file, &class_file);

    // setting up the stack
    vm_stack_t *VM_STACK = calloc(1, sizeof (vm_stack_t));

    // finding the main
    vm_method_info_t *main_method = calloc(1, sizeof (vm_method_info_t));
    vm_utf8_t method_name;

    vm_uint16_string_t *uint16_string;
    char *buffer = NULL;

    for (uint16_t i = 0; i < class_file.methods_count; i++) {
        method_name = class_file.constant_pool[class_file.methods[i].name_index].info.utf8_info;
        uint16_string = vm_utf8_to_uint16_t(method_name.length, method_name.bytes);

        buffer = realloc(buffer, ((uint16_string->length) * sizeof(char)));

        // first we print the name of the method to a buffer
        for (int j = 0; j < uint16_string->length; j++) {
            sprintf(&buffer[j], "%lc", uint16_string->string[j]);
        }

        // after that we check if the name is 'main'
        if (vm_strcmp(buffer, "main")) {
            // on success we save a reference to that method
            main_method = &(class_file.methods[i]);
            // and quit the loop
            break;
        } else {
            // if the method isn't the main method we set it to NULL
            main_method = NULL;
        }
    }

    // Check if we could find a main method
    if (main_method == NULL) {
        // Finishes the execution if we couldn't
        return "Couldn't find a main method";
    }

    // looking for the main code
    vm_code_t *main_code = calloc(1, sizeof (vm_code_t));
    vm_utf8_t attribute_name;

    for (uint16_t i = 0; i < main_method->attributes_count; i++) {
        attribute_name = class_file.constant_pool[main_method->attributes[i].attribute_name_index].info.utf8_info;
        uint16_string = vm_utf8_to_uint16_t(attribute_name.length, attribute_name.bytes);

        buffer = realloc(buffer, ((uint16_string->length) * sizeof(char)));

        // first we print the name of the method to a buffer
        for (int j = 0; j < uint16_string->length; j++) {
            sprintf(&buffer[j], "%lc", uint16_string->string[j]);
        }

        if (vm_strcmp(buffer, "Code")) {
            main_code = &(main_method->attributes[i].info.code_attribute);
            break;
        } else {
            main_code = NULL;
        }
    }

    if (main_code == NULL) {
        return "Couldn't find the code attribute of the main method";
    }

    vm_stack_t *MAIN_FRAME = VM_STACK;

    MAIN_FRAME->StringBuilder = NULL;
    MAIN_FRAME->local_variables = calloc(main_code->max_local, sizeof(vm_local_variables_t));
    MAIN_FRAME->operand_stack = calloc(1, sizeof(vm_ostack_t));
    MAIN_FRAME->constant_pool = class_file.constant_pool;
    MAIN_FRAME->next_frame = NULL;

    for (uint32_t pc = 0; pc < main_code->code_length;) {
        vm_opcodes(main_code->code, &pc, VM_STACK);
    }

    return "";
}
