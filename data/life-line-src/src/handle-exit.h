#ifndef HANDLE_EXIT_H
#define HANDLE_EXIT_H

#include <signal.h>         /* for signal, SIGINT, SIGTERM */
#include <stdlib.h> /* for exit */

/**
 * @note #include <stdlib.h>, for exit
 *
 * @date 2023-03-05
 * @author Cloudgen Wong
 */
void handle_exit(int sig);

/**
 * @note #include <signal.h> // for signal, SIGINT, SIGTERM
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void signal_exit();

#endif /* HANDLE_EXIT_H */

