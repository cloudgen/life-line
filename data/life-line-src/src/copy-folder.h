#ifndef COPY_FOLDER_H
#define COPY_FOLDER_H

#include <stdio.h> // for FILE, snprintf
#include <stdlib.h> // for malloc, free
#include <dirent.h> // for DIR, struct dirent, opendir, readdir, closedir
#include <sys/stat.h> // for struct stat, stat
#include <limits.h> // for PATH_MAX

/*
 * @note #include <stdio.h> // for FILE, snprintf
 * @note #include <stdlib.h> // for malloc, free
 * @note #include <dirent.h> // for DIR, struct dirent, opendir, readdir, closedir
 * @note #include <sys/stat.h> // for struct stat, stat
 * @note #include <limits.h> // for PATH_MAX
 *
 * @see copy_if_not_exist() to copy a file if it does not exist in the destination folder.
 * @see log_message_w_thread() to log error messages to the log file.
 * 
 * @date 2023-06-06
 * @author Cloudgen Wong
 */
void copyFolder(const char* sourceFolder, const char* destinationFolder, const char* thread_name, int debug_mode);

#endif /* COPY_FOLDER_H */