#include "set-file-permission.h"
#include "log-message.h"

/**
 * @file set-file-permission.c
 * @brief Set file permissions for a specified file.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

/**
 * @brief Set file permissions for a specified file.
 * 
 * This function sets the permissions of a specified file using the chmod function. 
 * It takes the filename and permissions as input parameters and attempts to set 
 * the permissions using the chmod function. The function logs the success or failure 
 * of the operation and returns a status code indicating the result.
 *
 * @param filename The path to the file.
 * @param permissions The permissions to be set for the file.
 * @param thread_name The name of the thread.
 * @param debug_mode The debug mode flag.
 *
 * @return 0 if the file permissions were successfully set, 1 otherwise.
 *
 * @details The function uses the chmod function to set the permissions of the specified file 
 * to the specified value. If the chmod function returns -1, indicating an error, an error message 
 * is logged and 1 is returned. Otherwise, a success message is logged and 0 is returned.
 *
 * @note This function requires the following include files:
 * @note #include <stdio.h> // for snprintf, NULL
 * @note #include <stdlib.h> // for malloc, free
 * @note #include <sys/stat.h> // for chmod
 *
 * @see debug_log_message_w_thread() to log debug messages.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int setFilePermissions(const char* filename, int permissions, const char* thread_name, int debug_mode) {
  if (chmod(filename, permissions) == -1) {
    char* log_message;
    int len = snprintf(NULL, 0, "Set file permissions for %s ..Failed..", filename);
    log_message = malloc(len + 1);
    snprintf(log_message, len + 1, "Set file permissions for %s ..Failed..", filename);
    debug_log_message_w_thread(debug_mode, thread_name, log_message);
    free(log_message);
    return 1;
  } else {
    char* log_message;
    int len = snprintf(NULL, 0, "Set file permissions for %s ..Success..", filename);
    log_message = malloc(len + 1);
    snprintf(log_message, len + 1, "Set file permissions for %s ..Success..", filename);
    debug_log_message_w_thread(debug_mode, thread_name, log_message);
    free(log_message);
    return 0;
  }
}