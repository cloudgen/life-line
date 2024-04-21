#ifndef CHECK_TUNNEL_H
#define CHECK_TUNNEL_H

#include <stdlib.h> // for access(), system(), malloc(), free()
#include <stdio.h> // for snprintf()
#include <unistd.h> // for F_OK, X_OK

/**
 * @note #include <stdio.h> // for access()
 * @note #include <stdlib.h> // for system()
 * @note #include <unistd.h> // for F_OK, X_OK
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void checkTunnel(const char* rootPriKey, const char* sshConfig, const char* thread_name, int debug_mode);

/**
 * @note #include <stdlib.h> // for access(), system(), malloc(), free()
 * @note #include <stdio.h> // for snprintf()
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void startTunnel(const char* rootPriKey, const char* sshConfig, const char* thread_name, int debug_mode);
void fixDocRoot(const char* thread_name, int debug_mode);

#endif /* CHECK_TUNNEL_H */