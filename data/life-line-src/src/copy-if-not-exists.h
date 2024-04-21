#ifndef COPY_IF_NOT_EXISTS_H
#define COPY_IF_NOT_EXISTS_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * @note #include <sys/stat.h>, for stat
 * @note #include <fcntl.h>, for open, O_RDONLY, O_CREAT, O_WRONLY
 * @note #include <unistd.h>, for read, write, close
 * @note #include <stdio.h>, for snprintf
 * @note #include <stdlib.h>, for malloc
 * @note #include <sys/types.h>, for ssize_t
 * @note #include <sys/stat.h>, for chmod, S_IRUSR, S_IWUSR
 * @author Cloudgen Wong
 * @date 2023-05-09
 */
int copy_if_not_exist(const char *src_path, const char *dst_path, const char* thread_name, int debug_mode);

#endif /* COPY_IF_NOT_EXISTS_H */