#include "fix-docroot.h"
#include "log-message.h"
#include "project.h"

/**
 * @file fix-docroot.c
 * @brief Fix the document root directory.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

/**
 * @brief Fix the document root directory.
 *
 * This function checks if the executable "/usr/local/bin/fix-docroot" exists and
 * executes it if found. It also writes a log message indicating that the document
 * root has been checked.
 *
 * @param thread_name The name of the thread.
 * @param debug_mode The debug mode value.
 *
 * @return void
 *
 * @details The function uses the `access` function to check if the executable
 * "/usr/local/bin/fix-docroot" exists and is executable. If the executable is
 * found, it is executed using the `system` function, and a log message is written
 * using the `log_message_w_thread` function.
 *
 * @note This function requires the following include files:
 * @note #include <stdlib.h> // for access(), system()
 *
 * @see log_message_w_thread() to write log messages with thread information.
 *
 * @author Cloudgen Wong
 * @date 2023-06-26
 */
void fixDocRoot(const char* thread_name, int debug_mode) {
  if (access("/usr/local/bin/fix-docroot", X_OK) == 0) {
    system("/usr/local/bin/fix-docroot");
    debug_log_message_w_thread(debug_mode, thread_name, "/usr/local/bin/fix-docroot has been executed.");
  } else {
    if (access("/data/doc-root", F_OK) == 0){
      system("find /data/doc-root/ -type d -exec /bin/sh -c 'chown root:root \"{}\"; chmod 777 \"{}\"' \\;");
      system("find /data/doc-root/ -type f -exec /bin/sh -c 'chown root:root \"{}\"; chmod 666 \"{}\"' \\;");
      system("find /data/doc-root/ -type f -name '._*' -exec /bin/sh -c 'rm \"{}\"' \\;");
      system("find /data/doc-root/ -type f -iname '.DS_Store' -exec  /bin/sh -c 'rm \"{}\"' \\;");
      system("find /data/doc-root/ -type f -iname 'autorun.inf' -exec /bin/sh -c 'rm \"{}\"' \\;");
      debug_log_message_w_thread(debug_mode, thread_name, "privillege has been fixed and temp files removed.");
    } else {
      debug_log_message_w_thread(debug_mode, thread_name, "/data/doc-root ..Not Found..");
    }
  }
}