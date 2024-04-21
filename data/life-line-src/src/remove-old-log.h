#ifndef REMOVE_OLD_LOG_H
#define REMOVE_OLD_LOG_H

/**
 * @file remove-old-log.h
 * @brief A thread function to periodically remove old log files from the specified directory.
 *
 * @author Cloudgen Wong
 * @date 2023-05-09
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define SECONDSINADAY (24 * 60 * 60)
#define DAYSTODELETEFILES (30 * SECONDSINADAY)

struct remove_log_args {
    char *log;
    int debug_mode;
};

void *thread_remove_old_logs_with_debug(void *arg);
void remove_old_logs_with_debug(const char *dir, const char *extension, const char *thread_name, int debug_mode);

#endif // REMOVE_OLD_LOG_H
