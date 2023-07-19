
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

int log_open() {
    return 0;
}

// just printf for now
// TODO: log files
void log_log(enum log_severity severity, const char *format, ...) {
    printf("[%s] ", severity_table[severity]);
    va_list list;
    va_start(list, format);
    vprintf(format, list);
    va_end(list);
    putc('\n', stdout);
}

