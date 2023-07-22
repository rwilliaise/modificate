
#ifndef SHARED_LOG_H_
#define SHARED_LOG_H_

enum log_severity {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
};

#ifndef NDEBUG
#define log_trace_s(var, fmt) log_log(LOG_TRACE, #var " = " #fmt, var)
#define log_trace(var) log_log(LOG_TRACE, #var " = %s", var)
#define log_debug(...) log_log(LOG_DEBUG, __VA_ARGS__)
#elif
#define log_trace_s(var, fmt)
#define log_trace(var)
#define log_debug(...)
#endif

int log_open();
void log_log(enum log_severity severity, const char *format, ...);
/** Similar functionality to perror(), however uses log_log */
void log_perror(const char *str);

#endif // SHARED_LOG_H_
