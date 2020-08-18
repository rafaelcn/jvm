#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

/**
 * @brief Logs formatted message to a pointed stream.
 * @param stream The stream to where the log will be sent. This value can range
 * from the stdout to a file on the disk.
 * @param s The message to be logged
 * @param line The line where the log has ocurred. Use with __LINE__
 * @param file The file where the log has occurred. Use with __FILE__
 * @param log_level The importance of the message being sent to stream
 */
void vm_log(FILE *stream, const char *s, int line, char *file, int log_level);

#endif /* LOGGER_H */