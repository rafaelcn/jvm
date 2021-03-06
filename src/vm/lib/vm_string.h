#ifndef VM_STRING_H
#define VM_STRING_H

#include <wchar.h>

/**
 * @brief Compares two strings, returning 1 if both strings are equal and 0
 * otherwise.
 * @param s The first string to use in the comparison.
 * @param s_ The second string to use in the comparison.
 */
int vm_strcmpl(const char *restrict s, const char *restrict s_);

/**
 * @brief Compares n chars from the back of the string, returning 1 if both
 * strings are equal and 0 otherwise.
 * @param s The first string to use in the comparison.
 * @param s_ The second string to use in the comparison.
 * @param n How many characters to compare both strings.
 */
int vm_strncmpl(const char *restrict s, const char *restrict s_, int n);


/**
 * @brief Compares two given strings, the implementation is equal to the one in
 * the C runtime library but differs on the return value.
 * @param s The first string to use in the comparison.
 * @param s_ The second string to use in the comparison.
 * @returns 1 if both strings are equal and 0 otherwise.
 */
int vm_strcmp(const char *restrict s, const char *restrict s_);

/**
 * @brief Compares n chars from both given strings, the implementation is equal
 * to the one in the C runtime library but differs on the return value.
 * @param s The first string to use in the comparison.
 * @param s_ The second string to use in the comparison.
 * @param n How many characters to compare both strings.
 * @returns 1 if both strings are equal and 0 otherwise.
 */
int vm_strncmp(const char *restrict s, const char *restrict s_, int n);

/**
 * @brief Splits a string s by a delimiter and returns the i-th string, indexed
 * by 0.
 * @param s The string to be split.
 * @param delim The delimiter used to split the string.
 * @param i The i-th token in the string s.
 */
char *vm_strspliti(const char *restrict s, const char *restrict delim, int i);


/**
 * @brief Splits a string s by a delimiter and returns an array of strings,
 * indexed by 0.
 * @param s The string to be split.
 * @param delim The delimiter used to split the string.
 * @returns array with N strings where N is the number of delimiters found + 1
 */
char** vm_strsplit(const char *restrict s, const char *restrict delim);


/**
 * @brief Searches for the first c character inside the string s.
 * @param s The string used to search the character.
 * @param c The character to be searched in the string
 * @returns An integer representing the position of the first character c in
 * the string s or, -1 if the character c could not be found.
 */
int vm_strchr(const char *s, const char c);

/**
 * @brief Counts how many times a delimiter/character appears on a string
 * @param s The string used to search the character.
 * @param c The character to be counted in the string
 * @returns An integer representing how many times a delimiter appears in the
 * string.
 */
size_t vm_strfreq(const char *s, const char c);

#endif /* VM_STRING_H */