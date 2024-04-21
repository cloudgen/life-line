#include "check-tunnel.h"
#include "log-message.h"
#include "project.h"

/**
 * @file check-tunnel.c
 * @brief Check the tunnel status using the root private key and SSH configuration file.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

/**
 * @brief Check the tunnel status using the root private key and SSH configuration file.
 *
 * This function checks the tunnel status by verifying the existence of the root private key
 * and the SSH configuration file. If they exist, it executes the appropriate tunnel check scripts.
 * The function also iterates over multiple tunnel check commands and executes them if they exist.
 *
 * @param rootPriKey The path to the root private key.
 * @param sshConfig The path to the SSH configuration file.
 * @param thread_name The name of the thread.
 * @param debug_mode The debug mode flag.
 *
 * @return void
 *
 * @details The function first checks if the root private key and SSH configuration file exist.
 * If both files exist, it proceeds to check the availability of tunnel check scripts.
 * The function checks two predefined tunnel check commands, TUNNEL_CMD1 and TUNNEL_CMD2.
 * If either command exists and is executable, it logs the tunnel check and executes the command.
 * Additionally, the function iterates over a range of numbers and checks tunnel commands with
 * appended numbers (e.g., TUNNEL_CMD1, TUNNEL_CMD2, TUNNEL_CMD3, etc.). If a command exists and is executable,
 * it logs the tunnel check and executes the command.
 *
 * @note This function requires the following include files:
 * @note #include <stdio.h> // for access()
 * @note #include <stdlib.h> // for system()
 * @note #include <unistd.h> // for F_OK, X_OK
 *
 * @see log_message_w_thread() to write a message to the log file with a thread name.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void checkTunnel(const char* rootPriKey, const char* sshConfig, const char* thread_name, int debug_mode) {
  char *s = NULL;
  char *cmd = NULL;
  int len;
  int i;
  // Check if the Root Private Key and sshConfig file exists
  if (access(rootPriKey, F_OK) == 0 ) {
    if(access(sshConfig, F_OK) == 0 ) {
      // Check if /usr/local/bin/check-tunnel exists and execute the shell script
      if (access(TUNNEL_CMD1, X_OK) == 0) {
        log_message_w_thread(thread_name, "Tunnel: " TUNNEL_CMD1 " has been checked.");
        system(TUNNEL_CMD1);
      } else if (access(TUNNEL_CMD2, X_OK) == 0) {
        system(TUNNEL_CMD2);
        log_message_w_thread(thread_name,"Tunnel: " TUNNEL_CMD2 " has been checked.");
      }   
    }

    for(i = 0; i < 10; i++) {
      len = snprintf(NULL, 0, "%s%d", TUNNEL_CMD1, i) + 1;
      cmd = malloc(len);
      snprintf(cmd, len, "%s%d", TUNNEL_CMD1, i);
      if (access(cmd, X_OK) == 0) {
        system(cmd);
        len = snprintf(NULL, 0, "Tunnel: %s has been checked.", cmd) + 1;
        s = malloc(len);
        snprintf(s, len, "Tunnel: %s has been checked.", cmd);
        log_message_w_thread(thread_name, s);
        free(s);
      }
      free(cmd);
      len = snprintf(NULL, 0, "%s%d", TUNNEL_CMD2, i) + 1;
      cmd = malloc(len);
      snprintf(cmd, len, "%s%d", TUNNEL_CMD2, i);
      if(access(cmd, X_OK) == 0) {
        system(cmd);
        len = snprintf(NULL, 0, "Tunnel: %s has been checked.", cmd) + 1;
        s = malloc(len);
        snprintf(s, len, "Tunnel: %s has been checked.", cmd);
        log_message_w_thread(thread_name, s);
        free(s);
      }
    }
  }
}

/**
 * @brief Start the tunnel with the provided configuration.
 *
 * This function starts the tunnel using the provided configuration files.
 * It checks if the root private key and sshConfig file exist and then executes
 * the corresponding tunnel shell scripts. It also checks for multiple tunnel
 * commands by appending numbers and executes them if found.
 *
 * @param rootPriKey The path to the root private key file.
 * @param sshConfig The path to the sshConfig file.
 * @param thread_name The name of the thread.
 * @param debug_mode The debug mode value.
 *
 * @return void
 *
 * @details The function first checks if the root private key and sshConfig file exist
 * using the `access` function. If both files exist, it proceeds to check if the
 * `/usr/local/bin/check-tunnel` command is executable using the `access` function.
 * If the command exists, it is executed using the `system` function, and a log message
 * is written using the `log_message_w_thread` function. If the command does not exist,
 * another command, `TUNNEL_CMD4`, is checked in the same manner and executed if available.
 *
 * Afterward, a loop is executed from 0 to 9. Within the loop, the function constructs
 * the tunnel command by appending the loop index to `TUNNEL_CMD3` and `TUNNEL_CMD4`.
 * The constructed command is then checked for executability using the `access` function.
 * If the command is executable, it is executed using the `system` function, and a log
 * message is written using the `log_message_w_thread` function.
 *
 * @note This function requires the following include files:
 * @note #include <stdlib.h> // for access(), system(), malloc(), free()
 * @note #include <stdio.h> // for snprintf()
 *
 * @see log_message_w_thread() to write log messages with thread information.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void startTunnel(const char* rootPriKey, const char* sshConfig, const char* thread_name, int debug_mode) {
  char *s = NULL;
  char *cmd = NULL;
  int len;
  int i;
  // Check if the Root Private Key and sshConfig file exists
  if (access(rootPriKey, F_OK) == 0 ) {
    if(access(sshConfig, F_OK) == 0 ) {
      // Check if /usr/local/bin/check-tunnel exists and execute the shell script
      if (access(TUNNEL_CMD3, X_OK) == 0) {
        system(TUNNEL_CMD3);
        log_message_w_thread(thread_name, "Tunnel: " TUNNEL_CMD3 " has been checked.");
      } else if (access(TUNNEL_CMD4, X_OK) == 0) {
        system(TUNNEL_CMD4);
        log_message_w_thread(thread_name,"Tunnel: " TUNNEL_CMD4 " has been checked.");
      } 
    }

    for(i = 0; i < 10; i++) {
      len = snprintf(NULL, 0, "%s%d", TUNNEL_CMD3, i) + 1;
      cmd = malloc(len);
      snprintf(cmd, len, "%s%d", TUNNEL_CMD3, i);
      if (access(cmd, X_OK) == 0) {
        system(cmd);
        len = snprintf(NULL, 0, "Tunnel: %s has been checked.", cmd) + 1;
        s = malloc(len);
        snprintf(s, len, "Tunnel: %s has been checked.", cmd);
        log_message_w_thread(thread_name, s);
        free(s);
      }
      free(cmd);
      len = snprintf(NULL, 0, "%s%d", TUNNEL_CMD4, i) + 1;
      cmd = malloc(len);
      snprintf(cmd, len, "%s%d", TUNNEL_CMD4, i);
      if(access(cmd, X_OK) == 0) {
        system(cmd);
        len = snprintf(NULL, 0, "Tunnel: %s has been checked.", cmd) + 1;
        s = malloc(len);
        snprintf(s, len, "Tunnel: %s has been checked.", cmd);
        log_message_w_thread(thread_name, s);
        free(s);
      }
    }
  }
}
