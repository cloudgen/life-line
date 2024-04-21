#ifndef FIX_DOCROOT_H
#define FIX_DOCROOT_H

#include <stdlib.h> // for access(), system()

/**
 * @note #include <stdlib.h> // for access(), system()
 *
 * @author Cloudgen Wong
 * @date 2023-06-26
 */
void fixDocRoot(const char* thread_name, int debug_mode);

#endif