#ifndef LIFE_LINE_H
#define LIFE_LINE_H


#include <stdlib.h> 
#include <unistd.h> 

/**
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int life_line(const char* thread_name, int debug_mode);

/**
 * @note #include <unistd.h> // for sleep() function
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int life_line_loop(const char* thread_name, int debug_mode);

void lifeLifeShortLink(const char* thread_name, int debug_mode);

#endif /* LIFE_LINE_H */