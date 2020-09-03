#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdlib.h>
#include <stdio.h>
#include "munit/munit.h"
#include "vm/lib/vm_string.h"


int main(int argc, char** argv) {
    printf("%s<--", argv[1]);

    int ret = vm_strcmpl(argv[1], "sim\n");
    //printf("%s", vm_strsplit("sim rafael", " ", 0));
    return ret;
}