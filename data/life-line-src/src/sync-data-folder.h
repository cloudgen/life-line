#ifndef SYNC_DATA_FOLDER_H
#define SYNC_DATA_FOLDER_H

#include <stdio.h> // for FILE, snprintf
#include <stdlib.h> // for malloc, free
#include <dirent.h> // for DIR, struct dirent, opendir, readdir, closedir
#include <limits.h> // for PATH_MAX
#include <string.h> // for strcmp
#include <sys/stat.h> // for struct stat, stat, S_ISDIR
#include <stdbool.h> // true, false

/*
 * @note #include <sys/stat.h> // for struct stat, stat, S_ISDIR
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
bool folderExists(const char* folderPath);

/**
 * @note #include <stdio.h> // for FILE, snprintf
 * @note #include <stdlib.h> // for malloc, free
 * @note #include <dirent.h> // for DIR, struct dirent, opendir, readdir, closedir
 * @note #include <limits.h> // for PATH_MAX
 * @note #include <string.h> // for strcmp
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int sync_data_folder(const char* thread_name, int debug_mode);

#endif /* SYNC_DATA_FOLDER_H */