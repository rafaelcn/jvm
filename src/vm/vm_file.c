#include "vm_file.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils/vm_checks.h"
#include "utils/vm_errors.h"
#include "utils/vm_logger.h"

uint8_t read_u1(file_t *file) {

    uint8_t value = 255;

    if (file->read < file->size) {
        value = file->data[file->read];
        file->read += 1;
    }

    return value;
}

uint16_t read_u2(file_t *file)
{
    uint16_t value = read_u1(file);

    value = value << 8;
    value = value | read_u1(file);

    return value;
}

uint32_t read_u4(file_t *file)
{
    uint32_t value = read_u1(file);

    for (int i = 0; i < 3; i++)
    {
        value = value << 8;
        value = value | read_u1(file);
    }

    return value;
}