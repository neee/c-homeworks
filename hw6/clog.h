//
// Created by Sergey Serdyuk on 16.04.2023.
//

#ifndef CLOG_H
#define CLOG_H

#include <stdio.h>

#define LOG_DEBUG(message) clog_log(CLOG_LEVEL_DEBUG, __FILE_NAME__, __LINE__, message)
#define LOG_INFO(message) clog_log(CLOG_LEVEL_INFO, __FILE_NAME__, __LINE__, message)
#define LOG_WARN(message) clog_log(CLOG_LEVEL_WARN, __FILE_NAME__, __LINE__, message)
#define LOG_ERROR(message) clog_log(CLOG_LEVEL_ERROR, __FILE_NAME__, __LINE__, message)

typedef enum {
    CLOG_LEVEL_DEBUG = 10,
    CLOG_LEVEL_INFO = 20,
    CLOG_LEVEL_WARN = 30,
    CLOG_LEVEL_ERROR = 40,
} clog_level;

void clog_init(clog_level log_level, FILE *log_file);

void clog_close(void);

void clog_log(clog_level log_level, char *file, int line, char *message);

#endif //CLOG_H
