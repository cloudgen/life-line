#ifndef MAKE_DIRECTORY_H
#define MAKE_DIRECTORY_H

/**
 * @file make-directory.h
 * @brief Create a directory and all its parent directories recursively
 *
 * @author Cloudgen Wong
 * @date 2023-04-13
 */

#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int make_directory(const char *path);

#endif /* MAKE_DIRECTORY_H */
