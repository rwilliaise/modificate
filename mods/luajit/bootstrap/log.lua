
FFI.cdef([[
enum log_severity {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
};

void log_log(enum log_severity severity, const char *format, ...);
]])

GLOBAL = GLOBAL or {} -- api present in the global environment for mods

-- logging utilities
GLOBAL.log = GLOBAL.log or {}

GLOBAL.log.trace = FFI.C.LOG_TRACE
GLOBAL.log.debug = FFI.C.LOG_DEBUG
GLOBAL.log.info = FFI.C.LOG_INFO
GLOBAL.log.warn = FFI.C.LOG_WARN
GLOBAL.log.error = FFI.C.LOG_ERROR

local function _stringify(...)
    local arr = {...}
    for i = 1, #arr do
        arr[i] = tostring(arr[i])
    end
    return table.concat(arr)
end

function GLOBAL.log.log(level, ...)
    FFI.C.log_log(level, "%s", _stringify(...))
end

function GLOBAL.print(...)
    GLOBAL.log.log(GLOBAL.log.info, ...)
end

