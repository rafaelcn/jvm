#include <stdio.h>
#include <stdlib.h>

#include "args_parser.h"

#include "vm/vm_info.h"
#include "vm/vm_entry.h"

#include "vm/lib/vm_string.h"

#include "vm/utils/vm_errors.h"
#include "vm/utils/vm_logger.h"
#include "vm/utils/vm_checks.h"

int usage();

int main(int argc, char** argv) {
    int ret = 0;

    if (argc < 2) {
        ret = usage();
    } else {
        const char *filename;

        // capture arguments sent through stdin
        args_t arguments = args_parse(argc, argv);
        size_t size = sizeof(arguments.flags) / sizeof(arg_t);

        for (size_t i = 0; i < size; i++) {

            if (!vm_valid_pointer((void*) arguments.flags[i].flag_name)) {
                continue;
            }

            if (vm_strcmp(arguments.flags[i].flag_name, "--version")) {
                printf("%s\n", VM_VERSION);
                break;
            } else if (vm_strcmp(arguments.flags[i].flag_name, "--help")) {
                ret = usage();
                break;
            } else if (vm_strcmp(arguments.flags[i].flag_name, "--execute")) {
                filename = arguments.flags[i].flag_value;

                if (!vm_valid_pointer((void*) filename)) {
                    char err[512];
                    sprintf(err, "missing argument <filename.class>");

                    vm_log(stdout, err, __LINE__, __FILE__, VM_LOG_WARNING);
                    printf("\n\n");
                    break;
                }

                // initializes execution of the nJVM (?)
                int ret = vm_init(filename);
            } else if (vm_strcmp(arguments.flags[i].flag_name, "--inform")) {
                filename = arguments.flags[i].flag_value;

                if (!vm_valid_pointer((void*) filename)) {
                    char err[512];
                    sprintf(err, "missing argument <filename.class>");

                    vm_log(stdout, err, __LINE__, __FILE__, VM_LOG_WARNING);
                    printf("\n\n");
                    break;
                }

                // initializes the execution of nJVM (?)
                int ret = vm_init(filename);
            } else {
                // this block of code would be better implemented as a hash map
                // using program arguments as key to prevent the following dummy
                // verification.
                if (i == size - 1) {
                    char err[512];
                    sprintf(err, "unknown argument %s", argv[1]);

                    vm_log(stdout, err, __LINE__, __FILE__, VM_LOG_INFO);
                    printf("\n\n");

                    ret = usage();
                    break;
                }
            }
        }


    }

    return ret;
}

int usage() {
    printf("%s\n\n", VM_VERSION);
    printf("usage:\n\t");
    printf("./nvjm.exe --execute <hello.class>\n\n");
    printf("available commands:\n\n");
    printf("\t--help\t\t\t- show this information\n");
    printf("\t--version\t\t- show the version of the nJVM\n");
    printf("\t--execute <class file>\t- executes a class file\n");
    printf("\t--inform  <class file>\t- shows information about the class file\n");

    return 0;
}
