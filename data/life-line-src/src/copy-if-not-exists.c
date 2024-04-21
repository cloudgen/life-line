#include "copy-if-not-exists.h"
#include "get-file-permission.h"
#include "log-message.h"
#include "set-file-permission.h"

/**
 * @file copy-if-not-exists.c
 * @brief Copies a source file to a destination file if the destination file does not exist.
 *
 * @author Cloudgen Wong
 * @date 2023-05-11
 */

/**
 * @brief Copies a source file to a destination file if the destination file does not exist.
 * 
 * @details This function checks if the destination file exists. If the destination file does not exist,
 * it copies the contents of the source file to the destination file. It also sets the appropriate permissions
 * for the destination file and logs the relevant messages.
 * 
 * @note #include <sys/stat.h>, for stat
 * @note #include <fcntl.h>, for open, O_RDONLY, O_CREAT, O_WRONLY
 * @note #include <unistd.h>, for read, write, close
 * @note #include <stdio.h>, for snprintf
 * @note #include <stdlib.h>, for malloc
 * @note #include <sys/types.h>, for ssize_t
 * @note #include <sys/stat.h>, for chmod, S_IRUSR, S_IWUSR
 * 
 * @param src_path The path of the source file.
 * @param dst_path The path of the destination file.
 * @param thread_name The name of the thread (for logging purposes).
 * @param debug_mode Debug mode indicator (1 for enabled, 0 for disabled).
 * 
 * @return int Returns 0 if the file is successfully copied or if the destination file already exists, 
 * and returns 1 if there is an error during the copying process.
 * 
 * @see debug_log_message_w_thread - Function to log debug messages with thread name
 * 
 * @author Cloudgen Wong
 * @date 2023-05-11
 */
int copy_if_not_exist(const char *src_path, const char *dst_path, const char* thread_name, int debug_mode) {
  struct stat buffer;
  int fd_src, fd_dst;
  char *s = NULL;
  int len;

  // Check if the destination file exists
  if (stat(dst_path, &buffer) != 0) {
    // If the destination file doesn't exist, copy the source file to the destination
    fd_src = open(src_path, O_RDONLY);
    if (fd_src == -1) {
      len = snprintf(NULL, 0, "Source file: %s not exists  ..No Action..", src_path);
      s = malloc(len + 1);
      snprintf(s, len + 1, "Source file: %s not exists  ..No Action..", src_path);
      debug_log_message_w_thread(debug_mode, thread_name, s);
      return 1;
    }

    fd_dst = open(dst_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd_dst == -1) {
      len = snprintf(NULL, 0, "Create %s ..Failed..", dst_path);
      s = malloc(len + 1);
      snprintf(s, len + 1, "Create %s ..Failed..", dst_path);
      debug_log_message_w_thread(debug_mode, thread_name, s);
      close(fd_src);
      return 1;
    }

    // Copy the contents of the source file to the destination file
    char buf[BUFSIZ];
    ssize_t num_read;
    while ((num_read = read(fd_src, buf, BUFSIZ)) > 0) {
      if (write(fd_dst, buf, num_read) != num_read) {
        len = snprintf(NULL, 0, "Write to %s ..Failed..", dst_path);
        s = malloc(len + 1);
        snprintf(s, len + 1, "Write to %s ..Failed..", dst_path);
        debug_log_message_w_thread(debug_mode, thread_name, s);
        close(fd_src);
        close(fd_dst);
        return 1;
      }
    }

    close(fd_src);
    close(fd_dst);
  } else {
    len = snprintf(NULL, 0, "Target already exists: %s ..No Action..", dst_path);
    s = malloc(len + 1);
    snprintf(s, len + 1, "Target already exists: %s ..No Action..", dst_path);
    debug_log_message_w_thread(debug_mode, thread_name, s);
    free(s);
    return 1;
  }
  // Get the source file attributes
  struct stat st;
  if (stat(src_path, &st) == -1) {
    len = snprintf(NULL, 0,  "Get destination file attributes: %s ..Failed..", src_path);
    s = malloc(len + 1);
    snprintf(s, len + 1, "Get destination file attributes: %s ..Failed..", src_path);
    debug_log_message_w_thread(debug_mode, thread_name, s);
    free(s);
    return 1;
  } else {
    // Set the destination file attributes to match the source file
    int permission = getPermissions(src_path, thread_name, debug_mode);
    if (permission == -1) {
      len = snprintf(NULL, 0,  "Get destination file %s permissions: %04o ..Failed..", dst_path, permission);
      s = malloc(len + 1);
      snprintf(s, len + 1, "Get destination file %s permissions: %04o ..Failed..", dst_path, permission);
      debug_log_message_w_thread(debug_mode, thread_name, s);
      free(s);
      return 1;
    } else {
      setFilePermissions(dst_path, permission, thread_name, debug_mode);
    }
  }
  return 0;
}