#ifndef VM_ERRORS_H
#define VM_ERRORS_H

// The maximum size of an error message.
#define VM_LOG_MAX_LENGTH 512

// List of possible ~errors~ and their numerical correspondents.
#define VM_LOG_INFO       0x00
#define VM_LOG_ERROR      0x01
#define VM_LOG_CRITICAL   0x02
#define VM_LOG_WARNING    0x03

#endif /* VM_ERRORS_H */