#include "make-directory.h"

/**
 * @file make-directory.c
 * @brief Create a directory and all its parent directories recursively
 *
 * @author Cloudgen Wong
 * @date 2023-04-13
 */

/**
 * @brief Create a directory and all its parent directories recursively.
 * 
 * This function creates a directory at the given path and all its parent directories
 * recursively if they do not exist. If the directory already exists, nothing happens.
 * 
 * @param path A pointer to a string containing the path of the directory to be created.
 * 
 * @return 0 on success, -1 on failure.
 * 
 * @details The function works by iterating over the path and creating each directory one
 * by one using the mkdir function. If a directory already exists, the function continues
 * to the next directory in the path. If an error occurs while creating a directory, the
 * function returns immediately with a failure code. The function assumes that the user
 * has permission to create directories in the specified path.
 * 
 * @note #include <stdio.h>, for sprintf
 * @note #include <stdlib.h>, for malloc, free
 * @note #include <string.h>, for strcpy, strlen
 * @note #include <sys/stat.h>, for mkdir
 * @note #include <errno.h>, for errno
 * 
 * @see mkdir
 * 
 * @author Cloudgen Wong
 * @date 2023-03-05
 */
int make_directory(const char *path) {
  char dir[1024];
  strcpy(dir, path);
  int len = strlen(dir);
  if (dir[len - 1] == '/') {
    dir[len - 1] = 0;
  }
  char *p = dir + 1;
  while (*p) {
    if (*p == '/') {
      *p = 0;
      if (mkdir(dir, 0700) && errno != EEXIST) {
        return -1;
      }
      *p = '/';
    }
    p++;
  }
  if (mkdir(dir, 0700) && errno != EEXIST) {
    return -1;
  }
  return 0;
}