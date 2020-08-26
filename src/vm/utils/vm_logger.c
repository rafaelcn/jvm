#include "vm_logger.h"
#include "vm_macros.h"
#include "vm_errors.h"

void vm_log(FILE *stream, const char *s, int line, char *file, int log_level) {

    // It is possible that the programmer may pass a string longer than
    // defined in the header of vm_errors, in that scenario it is definitely UB
    // per standard definition. Should we prevent that?
    char error[VM_LOG_MAX_LENGTH];

    // Implement something that shows the respective errc

    switch(log_level) {
    case VM_LOG_INFO:
        sprintf(error, ">>> %s | File: %s on line %d.", s, file, line);
        break;
    case VM_LOG_CRITICAL:
        sprintf(error, "%s>>> %s | File: %s on line %d. %s",
                ANSI_COLOR_RED, s, file, line, ANSI_COLOR_RESET);
        break;
    case VM_LOG_WARNING:
        sprintf(error, "%s>>> %s | File: %s on line %d. %s",
                ANSI_COLOR_YELLOW, s, file, line, ANSI_COLOR_RESET);
        break;
    }

    fprintf(stream, error, line, file);
}