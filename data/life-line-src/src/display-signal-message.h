#ifndef DISPLAY_SIGNAL_MESSAGE_H
#define DISPLAY_SIGNAL_MESSAGE_H

/**
 * @file display-signal-message.h
 * @brief Displays a message indicating a signal has been received and logs it
 *
 * @author Cloudgen Wong
 * @date 2023-06-07
 */

#include <stdlib.h> /* for NULL, malloc() and free() */
#include <stdio.h> /* for snprintf() */

/**
 * @note #include <stdlib.h> for NULL, malloc() and free()
 * @note #include <stdio.h> for snprintf()
 * 
 * @date 2023-06-07
 * @author Cloudgen Wong
 */
void display_signal_message(int sig);

#endif /* DISPLAY_SIGNAL_MESSAGE_H */