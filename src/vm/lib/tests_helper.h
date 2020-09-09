#ifndef VM_TESTS_HELPER_H
#define VM_TESTS_HELPER_H

/**
 * @authors Vinicius Gomes de Souza - 150047941
 *          Thiago Luis Rodrigues Pinho - 15/0065205
 * @brief Receives an argument string and slices it from start(inclusive) to end
 *        (exclusive)
 * @param input_string The string to be slliced
 * @param start 0 started index to start to slice from.
 * @param end 0 started index to end the slice. The end position will not be
 *              included in the returned string.
 * @returns Dynamically allocated new string containing an slice of the original
 * string. 
 */
char* string_substring(const char input_string[], int start, int end);

/**
 * @authors Vinicius Gomes de Souza - 150047941
 *          Thiago Luis Rodrigues Pinho - 15/0065205
 * @brief Receives an argument string and parses it into an array of substrings.
 * @param input_string The string to be split in substrings.
 * @param delimiter The character that is going to be used as a delimiter in the
 * splitting process.
 * @returns A dynamic array containing the dynamic sized substrings, without the
 *           delimiter character, of the input string. 
 */
char** arg_str_to_array_of_str(const char* input_string, const char delimiter);

#endif /* VM_STRING_H */