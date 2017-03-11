//
// Created by yanxq on 17/2/21.
//

#include <cstdio>
#include <string>
#include "smoke_jni_log.h"
#include "smoke_base.h"

static int __log_priority = smoke_priority::LOG_VERBOSE;

void set_log_priority(int priority) {
    __log_priority = priority;
}

static void console_println_va(int level, const char *tag, const char *function,
                               const char *fmt, va_list _vars) {
    if (level < __log_priority) {
        return;
    }

    size_t buf_size = vsnprintf(nullptr,0,fmt,_vars) + 1;
    char fmt_buf[buf_size];
    vsnprintf(fmt_buf,buf_size,fmt,_vars);

    unsigned int full_size = strlen(function) + strlen(fmt_buf) + 4;
    char full_buf[full_size];
    strcpy(full_buf,"[");
    strcat(full_buf,function);
    strcat(full_buf,"] ");
    strcat(full_buf,fmt_buf);
    smoke::_console_println(level,tag,full_buf);
}

void smoke_jni::console_println(int level, const char *tag, const char *function, const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list,fmt);
    console_println_va(level, tag, function, fmt, arg_list);
    va_end(arg_list);
}

void smoke_jni::console_verbose(const char *function, const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list,fmt);
    console_println_va(smoke_priority::LOG_VERBOSE, __global_tag, function, fmt, arg_list);
    va_end(arg_list);
}

void smoke_jni::console_debug(const char *function, const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list,fmt);

    console_println_va(smoke_priority::LOG_DEBUG, __global_tag, function, fmt, arg_list);

    va_end(arg_list);
}

void smoke_jni::console_info(const char *function, const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list,fmt);

    console_println_va(smoke_priority::LOG_INFO, __global_tag, function, fmt, arg_list);

    va_end(arg_list);
}

void smoke_jni::console_warn(const char *function, const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list,fmt);
    console_println_va(smoke_priority::LOG_WARN, __global_tag, function, fmt, arg_list);
    va_end(arg_list);
}

void smoke_jni::console_error(const char *function, const char *fmt, ...) {
    va_list arg_list;
    va_start(arg_list,fmt);
    console_println_va(smoke_priority::LOG_ERROR, __global_tag, function, fmt, arg_list);
    va_end(arg_list);
}