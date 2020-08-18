#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

/**
 * @brief Holds values for the flag name and the flag value.
 */
struct arg_t {
    const char *flag_name;
    const char *flag_value;
};

/**
 * @brief A list of arguments
 */
struct args_t {
    arg_t arguments[2];
};

/**
 * @brief Parses the arguments send to the CLI when calling the software.
 */
args_t args_parse(char **argv);

#endif /* ARGS_PARSER_H */