#ifndef SET_FILE_PERMISSION_H
#define SET_FILE_PERMISSION_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
 * @note #include <stdio.h> // for snprintf, NULL
 * @note #include <stdlib.h> // for malloc, free
 * @note #include <sys/stat.h> // for chmod
 *
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int setFilePermissions(const char* filename, int permissions, const char* thread_name, int debug_mode);

#endif /* SET_FILE_PERMISSION_H */