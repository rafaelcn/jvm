#include "vm_entry.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "vm_file.h"
#include "vm_settings.h"
#include "vm_constant_pool.h"

#include "utils/vm_errors.h"
#include "utils/vm_logger.h"
#include "utils/vm_checks.h"


int vm_init(const char* filename) {
    FILE *fd = fopen(filename, "rb");

    if (!vm_valid_pointer((void*) fd)) {
        char buffer[512];
        sprintf(buffer, "failed to read filename %s", filename);

        vm_log(stdout, buffer, __LINE__, __FILE__,
            VM_LOG_WARNING);
        return 1;
    }

    // initialize a java class struct
    file_t *file = (file_t *) malloc(sizeof(file_t));

    file->filename = filename;
    file->read = 0;

    // getting the size of the file
    fseek(fd, 0, SEEK_END);

    file->size = ftell(fd);

    fseek(fd, 0, SEEK_SET);

    // create the file buffer
    char* buffer = calloc(file->size+1, sizeof(char *));
    file->data = buffer;

    fread(buffer, sizeof(char *), file->size, fd);
    fclose(fd);

    buffer[file->size] = '\0';

    if (__debug_t) {
        for(size_t i = 0; i < file->size; i++) {
            printf("%.2X ", file->data[i]);
            file->read++;
        }

        printf("\n\n%ld in bytes size, %ld bytes read.\n", file->size,
               file->read);
    }

    // reset read information to future use
    file->read = 0;

    // TODO: Pass the information for the interpreter of java bytecode
    vm_load_constant_pool(file);

    return 0;
}