#include "check-tunnel.h"
#include "copy-folder.h"
#include "life-line.h"
#include "log-message.h"
#include "project.h"
#include "remove-old-log.h"
#include "sync-key.h"

/**
 * @file life-line.c
 * @brief Perform a series of operations to establish a secure connection and synchronize data.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

/**
 * @brief Perform a series of operations to establish a secure connection and synchronize data.
 * 
 * This function executes a series of steps to establish a secure connection and synchronize data.
 * It first synchronizes the private and public keys, then starts an SSH tunnel, and finally
 * copies a folder from the root to the data directory. The function provides support for
 * multi-threading by specifying the thread name and debug mode.
 *
 * @param thread_name The name of the thread executing the function.
 * @param debug_mode The debug mode flag indicating whether to enable debug output.
 *
 * @return The return value indicating the status of the function execution.
 *
 * @details The function calls the syncKey() function to synchronize the private and public keys
 * using the provided key file paths. It then logs a message indicating the time for checking
 * SSH key synchronization using the log_message_w_thread() function. Next, it starts an SSH tunnel
 * by calling the startTunnel() function with the root private key, SSH configuration file, thread name,
 * and debug mode. A log message is written to indicate the start of the SSH tunnel. Finally, the function
 * calls the copyFolder() function to copy a folder from the root directory to the data directory.
 *
 * @note This function requires the following include files:
 * N/A
 *
 * @see syncKey() function for synchronizing keys
 * @see log_message_w_thread() function for writing log messages with thread name
 * @see startTunnel() function for starting an SSH tunnel
 * @see copyFolder() function for copying folders
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int life_line(const char* thread_name, int debug_mode) {
  syncKey(DATA_PRIVATE_KEY, DATA_PUBLIC_KEY, ROOT_PRIVATE_KEY, ROOT_PUBLIC_KEY, thread_name, debug_mode);
  log_message_w_thread(thread_name,"Time for checking ssh keys synchronization.");
  startTunnel(ROOT_PRIVATE_KEY, TUNNEL_CONF, thread_name, debug_mode);
  log_message_w_thread(thread_name,"Starting SSH tunnel.");
  copyFolder(ROOT_DATA, DATA_ROOT, thread_name, debug_mode);
  return 0;
}

/**
 * @brief Perform a series of periodic operations in a loop.
 * 
 * This function executes a loop where it performs various operations at specific intervals.
 * It includes removing old logs, checking SSH key synchronization, fixing folders, and checking
 * the SSH tunnel. The function supports multi-threading by specifying the thread name and debug mode.
 *
 * @param thread_name The name of the thread executing the function.
 * @param debug_mode The debug mode flag indicating whether to enable debug output.
 *
 * @return The return value indicating the status of the function execution.
 *
 * @details The function initializes a counter variable and enters an infinite loop. In each iteration,
 * it increments the counter and checks if it exceeds 300. If the condition is met, it logs a message
 * indicating the time for removing old logs using the log_message_w_thread() function and calls the
 * remove_old_logs_with_debug() function to remove the logs. The counter is then reset to 0. Additionally,
 * the function checks if the counter is divisible by 10, 20, or 30, and performs corresponding operations
 * of checking SSH key synchronization, fixing folders, and checking the SSH tunnel, respectively. Each
 * operation is accompanied by a log message. Finally, the function sleeps for 1 second before continuing
 * to the next iteration of the loop.
 *
 * @note This function requires the following include files:
 * @note #include <unistd.h> // for sleep() function
 *
 * @see log_message_w_thread() function for writing log messages with thread name
 * @see remove_old_logs_with_debug() function for removing old logs
 * @see syncKey() function for synchronizing keys
 * @see fixDocRoot() function for fixing folders
 * @see checkTunnel() function for checking SSH tunnel
 *
 * @author Cloudgen Wong
 * @date 2023-06-26
 */
int life_line_loop(const char* thread_name, int debug_mode) {
  int counter = 0;
  while (1) {
    counter++;
    if (counter >= 3600) {
      log_message_w_thread(thread_name,"3600s: Time for removing Old Log.");
      remove_old_logs_with_debug(DATA_LOG, ".log", thread_name, debug_mode);
      counter = 0;
    }
    if (counter % 10 == 0) {
      log_message_w_thread(thread_name,"10s: Time for checking ssh keys synchronization.");
      syncKey(DATA_PRIVATE_KEY, DATA_PUBLIC_KEY, ROOT_PRIVATE_KEY, ROOT_PUBLIC_KEY, thread_name, debug_mode);
    }
    if (counter % 10 == 5) {
      log_message_w_thread(thread_name,"10s: Time for fix folder.");
      fixDocRoot(thread_name, debug_mode);
    }
    if (counter % 30 == 0) {
      log_message_w_thread(thread_name,"30s: Time for checking SSH tunnel.");
      checkTunnel(ROOT_PRIVATE_KEY, TUNNEL_CONF, thread_name, debug_mode);
    }
    sleep(1);
  }
  return 0;
}

/**
 * @note #include <stdlib.h> // for system()
 * @note #include <unistd.h> // for access()
 */
void lifeLifeShortLink(const char* thread_name, int debug_mode) {
  if (access("/usr/bin/life-line", X_OK) == 0) {
    if(!access("/usr/bin/ll-log-file", X_OK) == 0) {
      chdir("/usr/bin");
      system("ln -s life-line ll-log-file");
      log_message_w_thread(thread_name, "Short link for ll-log-file ..Created..");
    }
    if(!access("/usr/bin/ll-pid-file", X_OK) == 0) {
      chdir("/usr/bin");
      system("ln -s life-line ll-pid-file");
      log_message_w_thread(thread_name, "Short link for ll-pid-file ..Created..");
    }
    if(!access("/usr/bin/ll-log-msg", X_OK) == 0) {
      chdir("/usr/bin");
      system("ln -s life-line ll-log-msg");
      log_message_w_thread(thread_name, "Short link for ll-log-msg ..Created..");
    }
    if(!access("/usr/bin/ll-remove-old-log", X_OK) == 0) {
      chdir("/usr/bin");
      system("ln -s life-line ll-remove-old-log");
      log_message_w_thread(thread_name, "Short link for ll-remove-old-log ..Created..");
    }
    if(!access("/usr/bin/ll-sync-key", X_OK) == 0) {
      chdir("/usr/bin");
      system("ln -s life-line ll-sync-key");
      log_message_w_thread(thread_name, "Short link for ll-sync-key ..Created..");
    }
    if(!access("/usr/bin/ll-fix-docroot", X_OK) == 0) {
      chdir("/usr/bin");
      system("ln -s life-line ll-fix-docroot");
      log_message_w_thread(thread_name, "Short link for ll-fix-docroot ..Created..");
    }
  }
}