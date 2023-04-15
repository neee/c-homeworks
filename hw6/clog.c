#include "clog.h"

#include <stdlib.h>
#include <time.h>
#include <execinfo.h>

static FILE *log_file_ = NULL;
static clog_level log_level_;

void clog_init(clog_level log_level, FILE *log_file) {
    log_level_ = log_level;
    if (log_file != NULL) {
        log_file_ = log_file;
    } else {
        log_file_ = fopen("application.log", "a+");
    }
}

void clog_close(void) {
    if (log_file_ != NULL) {
        fclose(log_file_);
    }
}

static char *clog_level_to_char(clog_level log_level) {
    switch (log_level) {
        case 10:
            return "DEBUG";
        case 20:
            return "INFO";
        case 30:
            return "WARN";
        case 40:
            return "ERROR";
    }
}

static void print_trace(FILE *log_file) {
    void *array[10];
    char **strings;
    int size, i;

    size = backtrace(array, 10);
    strings = backtrace_symbols(array, size);
    if (strings != NULL) {
        fprintf(log_file, "\t\tObtained %d stack frames.\n", size);
        for (i = 0; i < size; i++) {
            fprintf(log_file, "\t\t%s\n", strings[i]);
        }
    }

    free(strings);
}

void clog_log(clog_level log_level, char *file, int line, char *message) {
    if (log_level >= log_level_) {
        fprintf(log_file_, "%lu %5s %s:%d | %s\n", (unsigned long) time(NULL), clog_level_to_char(log_level), file, line, message);
        fprintf(stdout, "%lu %5s %s:%d | %s\n", (unsigned long) time(NULL), clog_level_to_char(log_level), file, line, message);
    }
    if (log_level == CLOG_LEVEL_ERROR) {
        print_trace(log_file_);
        print_trace(stdout);
    }
}
