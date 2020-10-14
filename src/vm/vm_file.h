#ifndef VM_FILE_H
#define VM_FILE_H

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Represents a java .class file to be used when reading information from
 * the file.
 */
typedef struct file_t {
    /// The name of the .class file
    const char* filename;
    /// Pointer to the first byte read of the java .class file
    const char* data;
    /// size of the java .class file in bytes
    size_t size;
    /// Read bytes of the file. Used whenever you want to seek n bytes to the
    /// beginning of the file.
    size_t read;
} file_t;

/**
 * @brief Reads an unsigned byte (8 bits) from the .class file.
 * @param file A
 * @returns An unsigned char representing the byte read.
 */
//uint8_t read_u1(file_t *file);

/**
 * @brief Reads a two-byte unsigned number (16 bits in big-endian) from the
 * .class file.
 * @param file
 * @returns A unsigned short representing the two bytes read.
 */
//uint16_t read_u2(file_t *file);

/**
 * @brief Reads a four-byte unsigned number (32 bits in big-endian) from the
 * .class file.
 * @param file
 * @returns A unsigned int representing the four bytes read.
 */
//uint32_t read_u4(file_t *file);

#endif /* VM_FILE_H */