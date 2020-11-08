#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "machine.h"
#include "vm/lib/vm_string.h"

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
    vm_stack_frame_t *MAIN_FRAME = calloc(1, sizeof (vm_stack_frame_t));

    VM_STACK->frames_count = 1;
    VM_STACK->top_frame = MAIN_FRAME;

    MAIN_FRAME->constant_pool = class_file.constant_pool;
    MAIN_FRAME->local_variables_list = calloc(1, sizeof (vm_local_variables_list_t));
    MAIN_FRAME->operand_stack = calloc(1, sizeof (vm_operand_stack_t));
    MAIN_FRAME->next_frame = NULL;

    MAIN_FRAME->local_variables_list->local_variables_count = 0;
    MAIN_FRAME->local_variables_list->first_item = NULL;

    MAIN_FRAME->operand_stack->frames_count = 0;
    MAIN_FRAME->operand_stack->top_frame = NULL;

    // finding the main
    vm_method_info_t *main_method = calloc(1, sizeof (vm_method_info_t));
    vm_utf8_t method_name;
    uint16_t *uint16_string;
    char buffer[80];

    for (uint16_t i = 0; i < class_file.methods_count; i++) {
        method_name = class_file.constant_pool[class_file.methods[i].name_index].info.utf8_info;
        uint16_string = vm_utf8_to_uint16_t(method_name.length, method_name.bytes);

        // first we print the name of the method to a buffer
        for (int j = 0; j < method_name.length; j++) {
            sprintf(&buffer[j], "%lc", uint16_string[j]);
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

        // first we print the name of the method to a buffer
        for (int j = 0; j < method_name.length; j++) {
            sprintf(&buffer[j], "%lc", uint16_string[j]);
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

    for (uint32_t pc = 0; pc < main_code->code_length;) {
        pc = vm_opcodes(main_code->code, pc, VM_STACK);
    }

    return "";
}
