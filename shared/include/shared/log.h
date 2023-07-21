
#ifndef SHARED_LOG_H_
#define SHARED_LOG_H_

enum log_severity {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
};

int log_open();
void log_log(enum log_severity severity, const char *format, ...);
/** Similar functionality to perror(), however uses log_log */
void log_perror(const char *str);

#endif // SHARED_LOG_H_
