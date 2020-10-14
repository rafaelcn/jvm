#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

/**
 * @brief Holds values for the flag name and the flag value.
 */
typedef struct arg_t {
    const char *flag_name;
    const char *flag_value;
} arg_t;

/**
 * @brief A list of arguments
 */
typedef struct args_t {
    // array of parsed flags, filled after the args_parse is executed
    arg_t flags[5];
} args_t;

/**
 * @brief Parses the arguments send to the CLI when calling the software.
 */
args_t args_parse(int argc, char **argv);

#endif /* ARGS_PARSER_H */