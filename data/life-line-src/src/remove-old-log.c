#include "remove-old-log.h"
#include "log-message.h"

/**
 * @file remove-old-log.c
 * @brief A thread function to periodically remove old log files from the specified directory.
 *
 * @author Cloudgen Wong
 * @date 2023-04-13
 */

/**
 * @brief A thread function to periodically remove old log files from the specified directory
 * 
 * This function is called by a pthread_create() call in the main function. It takes a void pointer argument
 * which is cast to a const char pointer representing the directory path where log files are located.
 * The function then enters an infinite loop where it calls the remove_old_logs() function every 10 minutes
 * to remove old log files from the specified directory.
 * 
 * @param arg A void pointer argument representing the directory path where log files are located and debug_mode
 * 
 * @return void pointer
 * 
 * @details This function is called by a pthread_create() call in the main function to create a new thread.
 * The function sleeps for 10 minutes (600 seconds) and then calls the remove_old_logs() function to remove
 * old log files from the specified directory. It then repeats this process indefinitely until the program
 * is terminated.
 * 
 * @note #include <unistd.h> for sleep() function
 * 
 * @example 
 *
 *  #include <pthread.h>
 *  #include <stdlib.h>
 *  #include "remove-old-log.h"
 *  ...
 *    pthread_t remove_old_log_tid;
 *    struct remove_log_args * remove_log_args = malloc(sizeof(struct remove_log_args));
 *    remove_log_args->log = LOG_DIR;
 *    remove_log_args->debug_mode = 1;  // 1 for debug
 *    pthread_create(&remove_old_log_tid, NULL, thread_remove_old_logs_with_debug, (void *)remove_log_args);
 *
 * @see remove_old_logs_with_debug()
 * 
 * @date 2023-05-09
 * @author Cloudgen Wong
 */ 
void *thread_remove_old_logs_with_debug(void *arg){
  struct remove_log_args *args = (struct remove_log_args *) arg;
  char* thread_name = "Thread_remove_old_log";
  debug_log_message_w_thread(args->debug_mode, thread_name, "..Started..");
  while(1) {
    remove_old_logs_with_debug((const char *)args->log, "log", thread_name, args->debug_mode);
    sleep(600);
  }
}

/**
 * @brief Removes old log files in the specified directory.
 * 
 * This function scans the specified directory and removes any log files
 * that are more than one week old. The age of each file is determined by
 * its last modification time. If an error occurs while opening the
 * directory or removing a file, an error message will be printed to
 * standard error.
 * 
 * @param dir The path to the directory to scan.
 * 
 * @note #include <stdio.h>, for fprintf, stderr
 * @note #include <stdlib.h>, for malloc, free
 * @note #include <sys/types.h>, for DIR, opendir, readdir, closedir
 * @note #include <sys/stat.h>, for stat
 * @note #include <time.h>, for time, difftime
 * 
 * @return void
 * 
 * @details This function is used by the thread function `thread_remove_old_logs`
 * to periodically remove old log files in the background.
 * 
 * @see thread_remove_old_logs
 * 
 * @date 2023-06-02
 * @author Cloudgen Wong
 */

void remove_old_logs_with_debug(const char *dir, const char *extension, const char *thread_name, int debug_mode) {
  char *s = NULL;
  int len;
  DIR *d = opendir(dir);
  // fprintf(stderr, "Inside remove log: %s\n", dir);
  if (d == NULL) {
    len = snprintf(NULL, 0, "«%s» Error opening directory: %s",thread_name, dir);
    s = malloc(len + 1);
    snprintf(s, len + 1, "«%s» Error opening directory: %s", thread_name, dir);
    debug_log_message_w_thread(debug_mode, thread_name, s);
    free(s);
    return;
  }
  time_t now = time(NULL);
  struct dirent *entry;
  while ((entry = readdir(d)) != NULL) {
    // fprintf(stderr, "Checking: %s\n", entry->d_name);
    if (entry->d_type == DT_REG) {
      // fprintf(stderr, "Is File: %s\n", entry->d_name);
      // Check if the file has the desired extension
      char *file_extension = strrchr(entry->d_name, '.');
      if (file_extension != NULL && strcmp(file_extension, extension) == 0) {
        // File has the desired extension
        char path[1024];
        sprintf(path, "%s/%s", dir, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == 0) {
          double age = difftime(now, statbuf.st_mtime);
          if (age > DAYSTODELETEFILES) {
            if (remove(path) != 0) {
              len = snprintf(NULL, 0, "Error removing file: %s", path);
              s = malloc(len + 1);
              snprintf(s, len + 1, "Error removing file: %s",  path);
              debug_log_message_w_thread(debug_mode, thread_name, s);
              free(s);
            } else {
              len = snprintf(NULL, 0, "Removing file: %s", path);
              s = malloc(len + 1);
              snprintf(s, len + 1, "Removing file: %s",  path);
              debug_log_message_w_thread(debug_mode, thread_name, s);
              free(s);            
            }
            // fprintf(stderr, "Old: %s, age: %f\n", dir, age);
          } else {
            // fprintf(stderr, "Not old: %s, age: %f\n", dir, age);
          }
        } else {
          // fprintf(stderr, "Stat error: %s\n", entry->d_name);
        }
      } else {
          // fprintf(stderr, "Wrong extenstion: %s -> %s\n", entry->d_name, file_extension);
      }
    } else if (entry->d_type == DT_DIR) {
      // Handle subdirectories recursively
      if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        char subdirectory[1024];
        //fprintf(stderr, "Is Directory: %s\n", entry->d_name);
        sprintf(subdirectory, "%s/%s", dir, entry->d_name);
        //fprintf(stderr, "Dir: %s", subdirectory);
        remove_old_logs_with_debug(subdirectory, extension, thread_name, debug_mode);
      }
    }
  }
  closedir(d);
}
