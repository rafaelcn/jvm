#include <stdio.h>
#include <stdlib.h>

#include "args_parser.h"

#include "vm/vm_info.h"
#include "vm/vm_entry.h"

#include "vm/lib/vm_string.h"

#include "vm/utils/vm_errors.h"
#include "vm/utils/vm_logger.h"

int usage();

int main(int argc, char** argv) {
    int ret = 0;

    if (argc < 2) {
        ret = usage();
    } else {
        const char *filename;
        // capture arguments sent through stdin
        args_t arguments = args_parse(argv);

        size_t size = sizeof(arguments.flags) / sizeof(arg_t);
        for (size_t i = 0; i < size; i++) {
            // only two arguments are parsed at the moment.
            if (vm_strcmpl(arguments.flags[i].flag_name, "version")) {
                printf("%s\n", VM_VERSION);
                break;
            } else if (vm_strcmpl(arguments.flags[i].flag_name, "help")) {
                ret = usage();
                break;
            } else if (vm_strcmpl(arguments.flags[i].flag_name, "execute")) {
                filename = arguments.flags[i].flag_value;
            } else if (vm_strcmpl(arguments.flags[i].flag_name, "inform")) {
                filename = arguments.flags[i].flag_value;
            } else {
                // Create a new logger to ignore __LINE__ and __FILE__
                // parameters.
                vm_log(stdout, "unknown argument", __LINE__, __FILE__,
                    VM_LOG_INFO);

                ret = usage();
                break;
            }
        }

        int ret = vm_init(filename);
    }

    return ret;
}

int usage() {
    printf("%s\n\n", VM_VERSION);
    printf("usage:\n\t");
    printf("./nvjm.exe -filename <hello.class>\n\n");
    printf("available commands:\n\n");
    printf("\thelp\t\t\t- show this information\n");
    printf("\tversion\t\t\t- show the version of the nJVM\n");
    printf("\texecute <class file>\t- executes a class file\n");
    printf("\tinform  <class file>\t- shows information about the class file\n");

    return 0;
}
