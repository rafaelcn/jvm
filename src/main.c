#include <stdio.h>
#include <stdlib.h>

#include "args_parser.h"

#include "vm/vm_info.h"
#include "vm/vm_entry.h"

#include "vm/lib/vm_string.h"

#include "vm/utils/vm_logger.h"

int main(int argc, char** argv) {
    int ret = 0;

    if (argc < 2) {
        // TODO: log warning becuse of a missing filename.
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
            } else if (vm_strcmpl(arguments.flags[i].flag_name, "filename")) {
                filename = arguments.flags[i].flag_value;
            } else {
                // Create a new logger to ignore __LINE__ and __FILE__
                // parameters.
                //vm_log(stdout, "unknown argument", ...)
            }
        }

        int ret = vm_init(filename);
    }

    return ret;
}

