#ifndef MACROS_H
#define MACROS_H

#ifdef __linux__

// ANSI color escaping sequences
#define ANSI_COLOR_RED              "\x1b[31m"
#define ANSI_COLOR_GREEN            "\x1b[32m"
#define ANSI_COLOR_YELLOW           "\x1b[33m"
#define ANSI_COLOR_BRIGHT_YELLOW    "\x1b[33;1m"
#define ANSI_COLOR_BLUE             "\x1b[34;1m"
#define ANSI_COLOR_RESET            "\x1b[0m"

#endif // __linux__

#endif /* MACROS_H */