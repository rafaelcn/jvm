#ifndef TESTS_HELPER_H
#define TESTS_HELPER_H

/**
 * @brief Receives an argument string and slices it from start(inclusive) to end
 *        (exclusive)
 * @param input_string The string to be slliced
 * @param start 0 started index to start to slice from.
 * @param end 0 started index to end the slice. The end position will not be
 *              included in the returned string.
 * @returns Dynamically allocated new string containing an slice of the original
 * string.
 */
char* str_slice(const char input_string[], int start, int end);


/**
 * @brief Receives an argument string and parses it into an array of substrings.
 * @param input_string The string to be split in substrings.
 * @param delimiter The character that is going to be used as a delimiter in the
 * splitting process.
 * @returns A dynamic array containing the dynamic sized substrings, without the
 *           delimiter character, of the input string.
 */
char** test_strplit(const char* input_string, const char delimiter);

#endif /* TESTS_HELPER_H */