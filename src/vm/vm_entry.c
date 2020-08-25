#include "vm_entry.h"

#include <stdlib.h>
#include <stdio.h>

#include "utils/vm_errors.h"
#include "utils/vm_logger.h"

int vm_init(const char* filename) {
    FILE *fd = fopen(filename, "rb");

    if (!fd) {
        char* buffer;
        sprintf(buffer, "failed to read filename %s", filename);

        vm_log(stdout, buffer, __LINE__, __FILE__,
            VM_LOG_WARNING);
        return 1;
    }

    // create the file buffer
    const char* buffer[2048];
    // initialize a java class struct
    file_t *file = (file_t *) malloc(sizeof(file_t));

    file->filename = filename;
    file->data = buffer[0];
    file->size = 2048;
    file->read = 0;

    fread(buffer, sizeof(buffer), 1, fd);

    for(int i = 0; i < sizeof(buffer); i++) {
        printf("%x ", file->data[i]);
        file->read++;
    }

    printf("\n\nbytes read: %ld\n", file->read);

    // TODO: Pass the information for the interpreter of java bytecode

    return 0;
}