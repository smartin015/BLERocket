/*
 * Copyright (c) 2012 David Rodrigues
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef __MACROLOGGER_H__
#define __MACROLOGGER_H__

#include <time.h>
#include <string.h>

// === auxiliar functions
static inline char *timenow();

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define NO_LOG          0x00
#define ERROR_LEVEL     0x01
#define INFO_LEVEL      0x02
#define DEBUG_LEVEL     0x03

#ifndef LOG_LEVEL
#define LOG_LEVEL   INFO_LEVEL
#endif

#ifdef __OBJC__

#define PRINTFUNCTION(format, ...)      objc_print(@format, __VA_ARGS__)
#else
#define PRINTFUNCTION(format, ...)      fprintf(stderr, format, __VA_ARGS__)

#endif

#define LOG_FMT             "%s %s %s:%s:%d: "
#define LOG_ARGS(tag, LOG_TAG)  LOG_TAG, timenow(), tag, __FUNCTION__, __LINE__

#define NEWLINE     "\n"

#define ERROR_TAG   "E"
#define INFO_TAG    "I"
#define DEBUG_TAG   "D"

#if LOG_LEVEL >= DEBUG_LEVEL
#define ESP_LOGD(tag, message, args...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(tag, DEBUG_TAG), ## args)
#else
#define ESP_LOGD(tag, message, args...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define ESP_LOGI(tag, message, args...)      PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(tag, INFO_TAG), ## args)
#else
#define ESP_LOGI(tag, message, args...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define ESP_LOGE(tag, message, args...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(tag, ERROR_TAG), ## args)
#else
#define ESP_LOGE(tag, message, args...)
#endif

static inline char *timenow() {
    static char buffer[64];
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);

    return buffer;
}

#endif
