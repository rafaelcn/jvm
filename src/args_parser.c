#include "args_parser.h"

#include <stdlib.h>

args_t args_parse(int argc, char **argv) {
    args_t parsed;
    parsed.flags[0].flag_name = "";
    parsed.flags[0].flag_value = "";
    parsed.flags[1].flag_name = "";
    parsed.flags[1].flag_value = "";


    for(int i = 0; i < 4 && i < argc; i = i + 2)
    {
        parsed.flags[i].flag_name = argv[i];
        if(i+1 < argc)
        {
            parsed.flags[i].flag_value = argv[i+1];
        }
    }

    return parsed;
}