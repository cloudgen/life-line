#ifndef _SET_PERMISSION_H
#define _SET_PERMISSION_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @note #include <stdio.h> // for FILE, fscanf, popen, pclose
 * @note #include <stdlib.h> // for malloc, free
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int getPermissions(const char* filename, const char* thread_name, int debug_mode);

#endif
