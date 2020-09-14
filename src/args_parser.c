#include "args_parser.h"

#include <stdlib.h>
#include <stdio.h>

args_t args_parse(int argc, char **argv) {
    args_t parsed;
    printf("%d", argc);
    printf("%s", argv[0]);
    for(int i = 0; i < argc; i++)
    {   
        printf("%s", argv[i]);
        if(argv[i][0] != '-') return parsed;
        if(argv[i] == "-version" || argv[i] == "-help"
            || argv[i] == "-inform" || argv[i] == "-execute") {
            parsed.flags[i/2].flag_name = argv[i];
            parsed.flags[i/2].flag_value = argv[i+1];
        }
    }

    return parsed;
}