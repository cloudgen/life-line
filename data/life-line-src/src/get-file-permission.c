#include "get-file-permission.h"
#include "log-message.h"

/**
 * @file get-file-permission.c
 * @brief Get the permissions of a file
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

/**
 * @brief Get the permissions of a file.
 * 
 * This function retrieves the permissions of a specified file. It uses the "busybox stat" command
 * to get the file's permissions in octal format. The function then parses the output of the command
 * and returns the permissions as an integer.
 *
 * @param filename The path to the file.
 * @param thread_name The name of the thread.
 * @param debug_mode The debug mode flag.
 *
 * @return The permissions of the file as an integer.
 *
 * @details The function constructs a command string using the specified filename and calls the
 * "busybox stat" command to retrieve the permissions. If the command execution fails, an error
 * message is logged and -1 is returned. If the permissions cannot be retrieved from the command
 * output, an error message is logged and -1 is returned. Otherwise, the permissions are parsed
 * from the output and returned as an integer value.
 *
 * @note This function requires the following include files:
 * @note #include <stdio.h> // for FILE, fscanf, popen, pclose
 * @note #include <stdlib.h> // for malloc, free
 *
 * @see log_message_w_thread() to log error messages.
 * @see debug_log_message_w_thread() to log debug messages.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int getPermissions(const char* filename, const char* thread_name, int debug_mode) {
    char* log_message = NULL;
    int len = 0;

    char command[512];
    sprintf(command, "busybox stat -c '%%a' %s", filename);

    FILE* fp = popen(command, "r");
    if (fp == NULL) {
        len = snprintf(NULL, 0, "The execution of command: '%s'  ..Failed..", command) + 1;
        log_message = (char *) malloc( len );
        snprintf(log_message, len, "The execution of command: '%s'  ..Failed..", command);
        return -1;
    }

    int permissions;
    if (fscanf(fp, "%o", &permissions) != 1) {
        len = snprintf(NULL, 0, "Unable to retrieve file permissions: %s  ..Error..\n", filename) + 1;
        log_message = (char*)malloc(len);
        snprintf(log_message, len, "Unable to retrieve file permissions: %s  ..Error..\n", filename);
        log_message_w_thread( thread_name, log_message);
        free(log_message);
        pclose(fp);
        return -1;
    }

    pclose(fp);

    len = snprintf(NULL, 0, "File: %s, With permissions (Octal): %03o\n", filename, permissions) + 1;
    log_message = (char *)malloc( len );
    snprintf(log_message, len, "File: %s, With permissions (Octal): %03o\n", filename, permissions);
    debug_log_message_w_thread(debug_mode, thread_name, log_message);
    free(log_message);
    return permissions;
}
