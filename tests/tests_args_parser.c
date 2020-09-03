#define MUNIT_ENABLE_ASSERT_ALIASES

#include <stdlib.h>
#include <stdio.h>

#include "munit/munit.h"
#include "vm/lib/vm_string.h"


int main(int argc, char** argv) {

    int cap = vm_strchr("rafael", 'l');
    int ret = vm_strncmpl(argv[1], "sim", 3);
    int ret2 = vm_strcmpl("sim", "sim");
    int ret3 = vm_strcmpl("sim", "sim1231");

    assert(cap == 5);
    assert(ret == 1);
    assert(ret2 == 1);
    assert(ret3 == 0);

    //printf("%s", vm_strsplit("sim rafael", " ", 0));
    return 0;
}