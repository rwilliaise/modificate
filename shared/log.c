
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include <shared/log.h>

static const char *severity_table[] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
};

#ifdef __linux__
static const char *severity_colors[] = {
    "\x1B[36m",
    "\x1B[36m",
    "\x1B[36m",
    "\x1B[33m",
    "\x1B[31m",
};
#define RESET "\x1B[m"
#else
static const char *severity_colors[] = {
    "",
    "",
    "",
    "",
    "",
};
#define RESET ""
#endif

int log_open() {
    return 0;
}

// just printf for now
// TODO: log files, multithreading safety
void log_log(enum log_severity severity, const char *format, ...) {
    printf("%s[%s] ", severity_colors[severity], severity_table[severity]);
    va_list list;
    va_start(list, format);
    vprintf(format, list);
    va_end(list);
    printf("%s\n", RESET);
}

