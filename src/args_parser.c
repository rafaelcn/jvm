#include "args_parser.h"

#include "vm/lib/vm_string.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

args_t args_parse(int argc, char **argv) {
    args_t parsed;

    // Allocate a buffer big enough to hold every argument passed.
    // FIXME: THIS IS INSECURE.
    char *all_args = calloc(sizeof(char), 8196);

    for (size_t i = 1; i < argc; i++) {
        strcat(strcat(all_args, " "), argv[i]);
    }

    for (size_t i = 0; i < argc-1; i++) {
        char *flag = vm_strspliti(all_args, " ", i);

        parsed.flags[i].flag_name = flag;

        if (i+1 <= argc-1) {
            char *value = vm_strspliti(all_args, " ", i+1);

            if (!vm_strncmp(value, "--", 2)) {
                parsed.flags[i].flag_value = value;
                // if this is a value then skip the next check
                ++i;
            } else {
                parsed.flags[i].flag_value = "";
            }
        }
    }

    return parsed;
}