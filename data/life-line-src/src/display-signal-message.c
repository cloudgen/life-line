#include "display-signal-message.h"
#include "log-message.h"

/**
 * @file display-signal-message.c
 * @brief Displays a message indicating a signal has been received and logs it
 *
 * @author Cloudgen Wong
 * @date 2023-06-07
 */

/**
 * @brief Displays a message indicating a signal has been received and logs it
 *
 * @param sig The signal received
 *
 * @note This function requires the following include files:
 * @note #include <stdlib.h> for NULL, malloc() and free()
 * @note #include <stdio.h> for snprintf()
 * 
 * @see log_message()
 * 
 * @date 2023-06-07
 * @author Cloudgen Wong
 */
void display_signal_message(int sig){
  char *s = NULL;
  int len = 0;
  len = snprintf(NULL, 0, "«Thread_main» Signal '%d' ..Terminated..", sig) + 1;
  s = (char *) malloc(len);
  snprintf(s, len, "«Thread_main» Signal '%d' ..Terminated..", sig);
  log_message(s);
  free(s);
}