#include "project.h"
#include "log-message.h"
#include "make-directory.h"

/**
 * @file log-message.c
 * @brief Write a message to the log file with timestamp and process ID
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

char* logDirname(const char *data_log, const char* app) {
  int pathLen = strlen(data_log);
  char* log_dir=NULL;
  if(data_log[pathLen - 1]=='/') {
    int len = snprintf(NULL, 0, "%s%s",data_log, app) + 1; 
    log_dir = malloc(len);
    snprintf(log_dir, len ,"%s%s",data_log, app); 
  } else {
    int len = snprintf(NULL, 0, "%s/%s",data_log, app) + 1; 
    log_dir = malloc(len);
    snprintf(log_dir, len ,"%s/%s",data_log, app); 
  }
  return log_dir;
}

char* prepareLogDir(const char *data_log, const char* app) {
  char *log_dir = logDirname(data_log, app);
  make_directory(log_dir);
  return log_dir;
}

char* logFilenameWithTimeStamp(int debug_mode, char *log_dir, char* app){
  int len, pathLen;
  char* filename;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char tm_str[20];
  strftime(tm_str, sizeof(tm_str), "%Y-%m-%d", &tm);
  pathLen = strlen(log_dir);
  if (debug_mode) {
    if(log_dir[pathLen - 1]=='/'){
      len = snprintf(NULL, 0, "%s%s-%s-debug.log",log_dir, app, tm_str) + 1;
      filename = malloc(len);
      snprintf(filename, len, "%s%s-%s-debug.log",log_dir, app, tm_str);
    } else {
      len = snprintf(NULL, 0, "%s/%s-%s-debug.log",log_dir, app, tm_str) + 1;
      filename = malloc(len);
      snprintf(filename, len, "%s/%s-%s-debug.log",log_dir, app, tm_str);
    }
  } else {
    if(log_dir[pathLen - 1]=='/'){
      len = snprintf(NULL, 0, "%s%s-%s.log",log_dir, app, tm_str) + 1;
      filename = malloc(len);
      snprintf(filename, len, "%s%s-%s.log",log_dir, app, tm_str);
    }else {
      len = snprintf(NULL, 0, "%s/%s-%s.log",log_dir, app, tm_str) + 1;
      filename = malloc(len);
      snprintf(filename, len, "%s/%s-%s.log",log_dir, app, tm_str);
    }
  }
  return filename;
}

void logMessageWithLogName(int debug_mode, int useVersion, char *logFile, int pid, char *app, char *appName, const char *thread, const char *msg) {
  char timestamp[100];
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm);
  if (debug_mode) {
    if(strcmp(thread,"") == 0) {
      if(useVersion) {
        fprintf(stderr, "%s %s@%s #%d ] %s\n",timestamp, appName, APP_VERSION, pid, msg);
      } else {
        fprintf(stderr, "%s %s #%d ] %s\n",timestamp, appName, pid, msg);
      }
    } else {
      if(useVersion) {
        fprintf(stderr, "%s %s@%s #%d ]   «%s» %s\n",timestamp, appName, APP_VERSION, pid, thread, msg);
      } else {
        fprintf(stderr, "%s %s #%d ]   «%s» %s\n",timestamp, appName, pid, thread, msg);
      }
    }
  }
  FILE *fp = fopen(logFile, "a");
  if (fp == NULL) {
    return;
  }
  if(strcmp(thread,"") == 0) {
    if(useVersion) {
      fprintf(fp, "%s %s@%s #%d ] %s\n",timestamp, appName, APP_VERSION, pid, msg);
    } else {
      fprintf(fp, "%s %s #%d ] %s\n",timestamp, appName, pid, msg);
    }
  } else {
    if(useVersion) {
      fprintf(fp, "%s %s@%s #%d ]   «%s» %s\n",timestamp, appName, APP_VERSION, pid, thread, msg);
    } else {
      fprintf(fp, "%s %s #%d ]   «%s» %s\n",timestamp, appName, pid, thread, msg);
    }
  }
  fclose(fp);
}

/**
 * @brief Write debug log messages to a file with a timestamp and process ID.
 * 
 * This function writes a debug log message to a file named "APP-YYYY-MM-DD-debug.log"
 * located in the directory specified by the LOG_DIR macro. The log message includes a 
 * timestamp and process ID.
 * 
 * @param useVersion A flag indicating whether or not to display the version.
 * @param debug_mode A flag indicating whether or not debug mode is enabled.
 * @param app A string representing the application's command name.
 * @param appName A string representing the application's full name.
 * @param thread A string representing the thread ID.
 * @param msg The debug log message to be written to the log file.
 * 
 * @return void
 * 
 * @details The log message is written to a file named "APP-YYYY-MM-DD.log"
 * in the directory specified by the LOG_DIR macro. The log file is opened in "append" mode.
 * If the file cannot be opened, an error message is printed to the console, and the function
 * returns without writing the log message. The log message includes a timestamp and process ID,
 * and is written in the following format:
 * 
 *     YYYY-MM-DD HH:MM:SS appNameAPP_VERSION #PID ] message
 * 
 * Where:
 * - YYYY-MM-DD is the date on which the log message was written
 * - HH:MM:SS is the time at which the log message was written
 * - appName and APP_VERSION are preprocessor macros defined in config.h
 * - PID is the process ID of the process that wrote the log message
 * - message is the log message provided as an argument to the function
 * 
 * @note This function requires the following include files:
 * @note #include <stdio.h> // for FILE, fopen, fclose, fprintf, perror
 * @note #include <stdlib.h> // for pid_t
 * @note #include <unistd.h> // for getpid
 * @note #include <time.h> // for time, localtime, strftime
 * 
 * @see log_message_init() to initialize the log file directory.
 * 
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void logMessage(int useVersion, int debug_mode, char *app, char *appName, const char *thread, const char *msg) {
  int len = snprintf(NULL, 0, "%s%s", DATA_LOG, app) + 1;
  char* log_dir = malloc(len);
  snprintf(log_dir, len,  "%s%s", DATA_LOG, app);
  make_directory(log_dir);
  int pid = (int)getpid();
  char *filename = logFilenameWithTimeStamp(debug_mode, log_dir, app);
  logMessageWithLogName(debug_mode, useVersion, filename, pid, app, appName, thread, msg);
  free(filename);
  free(log_dir);
}

void logMessageWithPid(int useVersion, int debug_mode, int pid, char *app, char *appName, const char *thread, const char *msg) {
  int len = snprintf(NULL, 0, "%s%s", DATA_LOG, app) + 1;
  char* log_dir = malloc(len);
  snprintf(log_dir, len,  "%s%s", DATA_LOG, app);
  make_directory(log_dir);
  char *filename = logFilenameWithTimeStamp(debug_mode, log_dir, app);
  logMessageWithLogName(debug_mode,useVersion, filename, pid, app, appName, thread, msg);
  free(filename);
  free(log_dir);
}

/**
 * @brief Initialize the log file for a given thread.
 *
 * This function creates the log directory if it doesn't exist and writes a start message to the log file.
 *
 * @param thread_name The name of the thread.
 *
 * @return 0 if the log initialization is successful, 1 otherwise.
 *
 * @details The function attempts to create the log directory specified by the `LOG_DIR` constant.
 * If the directory creation fails, an error message is printed to stderr and the function returns with a value of 1.
 * Otherwise, a start message is written to the log file using the `log_message` function.
 * The start message indicates the initialization of the log file.
 *
 * @note This function requires the following include files:
 * @note #include <stdio.h> // for fprintf(), stderr
 *
 * @see log_message() to write messages to the log file.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int init_log(const char* thread_name) {
  if (make_directory(LOG_DIR) != 0) {
    fprintf(stderr, "  «%s» Creating directory to log ..Error..\n", thread_name);
    // No log to keep
    return 1;
  }
  log_message("====== State: .*STARTED*..................... ======");
  return 0;
}

int init_log_appName(int debug_mode, const char* thread_name, char* appName) {
  if (make_directory(LOG_DIR) != 0) {
    fprintf(stderr, "  «%s» Creating directory to log ..Error..\n", thread_name);
    // No log to keep
    return 1;
  }
  advanced_log_appname(debug_mode, "", appName, "====== State: .*STARTED*..................... ======");
  return 0;
}
/**
 * @brief Write a message to the log file with timestamp and process ID.
 * 
 * This function writes a message to the log file with timestamp and process ID.
 * The log file is located in the LOG_DIR directory with the format APP-YYYY-MM-DD.log.
 *
 * @param app The application name.
 * @param msg The message to be written to the log file.
 *
 * @return void
 *
 * @details This function generates a log message with a timestamp and process ID and writes it to a log file.
 * The log file is stored in the LOG_DIR directory with the naming convention APP-YYYY-MM-DD.log, where APP
 * represents the application name and YYYY-MM-DD represents the current date. The log message includes the
 * timestamp, application name, process ID, and the provided message. The log file is opened in "append" mode,
 * and if it doesn't exist, it will be created. If there is an error opening the file, the function will return
 * without writing the log message.
 *
 * @note This function does not require any include files.
 *
 * @see init_log() to initialize the log file directory.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void simple_log(char* app, char* msg) {
  logMessage(0, 0, app, app, "", msg);
}

/**
 * @brief Write a message to the log file with timestamp and process ID.
 * 
 * This function writes a message to the log file with timestamp and process ID.
 * The log file is located in the LOG_DIR directory with the format APP-YYYY-MM-DD.log.
 *
 * @param pid The pid of this application.
 * @param app The application name.
 * @param msg The message to be written to the log file.
 *
 * @return void
 *
 * @details This function generates a log message with a timestamp and process ID and writes it to a log file.
 * The log file is stored in the LOG_DIR directory with the naming convention APP-YYYY-MM-DD.log, where APP
 * represents the application name and YYYY-MM-DD represents the current date. The log message includes the
 * timestamp, application name, process ID, and the provided message. The log file is opened in "append" mode,
 * and if it doesn't exist, it will be created. If there is an error opening the file, the function will return
 * without writing the log message.
 *
 * @note This function does not require any include files.
 *
 * @see init_log() to initialize the log file directory.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void simple_log_with_pid(int pid, char* app, char* msg) {
  logMessageWithPid(0, 0, pid, app, app, "", msg);
}

/**
 * @brief Write a message to the log file with timestamp and process ID, including advanced options.
 * 
 * This function writes a message to the log file with timestamp and process ID. It provides advanced options
 * for logging, such as specifying a debug mode, thread name, and message. The log file is located in the
 * LOG_DIR directory with the format APP-YYYY-MM-DD.log.
 *
 * @param debug_mode The debug mode for logging. If set to 1, additional debug information is included in the log message.
 * @param thread The name of the thread associated with the log message.
 * @param msg The message to be written to the log file.
 *
 * @return void
 *
 * @details This function generates a log message with a timestamp, process ID, and advanced options and writes it
 * to a log file. The log file is stored in the LOG_DIR directory with the naming convention APP-YYYY-MM-DD.log,
 * where APP represents the application name and YYYY-MM-DD represents the current date. The log message includes
 * the timestamp, application name, process ID, debug mode, thread name, and the provided message. The log file is
 * opened in "append" mode, and if it doesn't exist, it will be created. If there is an error opening the file,
 * the function will return without writing the log message.
 *
 * @note This function requires the following include files:
 * @note #include <stdlib.h> // for snprintf, malloc, free
 *
 * @see log_message() for a simplified version of the log function.
 * @see init_log() to initialize the log file directory.
 *
 * @author Cloudgen Wong
 * @date 2024-04-19
 */
void advanced_log_appname(int debug_mode, const char *thread, char *appName, const char *msg) {
  char* app = NULL;
  int len = snprintf(NULL, 0, APP) + 1;
  app = malloc(len);
  snprintf(app, len, APP);
  len = snprintf(NULL, 0, APP_NAME) + 1;
  logMessage(1, debug_mode, app, appName, thread, msg);
  free(app);
}

/**
 * @brief Write a message to the log file with timestamp and process ID, including advanced options.
 * 
 * This function writes a message to the log file with timestamp and process ID. It provides advanced options
 * for logging, such as specifying a debug mode, thread name, and message. The log file is located in the
 * LOG_DIR directory with the format APP-YYYY-MM-DD.log.
 *
 * @param debug_mode The debug mode for logging. If set to 1, additional debug information is included in the log message.
 * @param thread The name of the thread associated with the log message.
 * @param msg The message to be written to the log file.
 *
 * @return void
 *
 * @details This function generates a log message with a timestamp, process ID, and advanced options and writes it
 * to a log file. The log file is stored in the LOG_DIR directory with the naming convention APP-YYYY-MM-DD.log,
 * where APP represents the application name and YYYY-MM-DD represents the current date. The log message includes
 * the timestamp, application name, process ID, debug mode, thread name, and the provided message. The log file is
 * opened in "append" mode, and if it doesn't exist, it will be created. If there is an error opening the file,
 * the function will return without writing the log message.
 *
 * @note This function requires the following include files:
 * @note #include <stdlib.h> // for snprintf, malloc, free
 *
 * @see log_message() for a simplified version of the log function.
 * @see init_log() to initialize the log file directory.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void advanced_log(int debug_mode, const char *thread, const char *msg) {
  char* app = NULL;
  char* appName = NULL;
  int len = snprintf(NULL, 0, APP) + 1;
  app = malloc(len);
  snprintf(app, len, APP);
  len = snprintf(NULL, 0, APP_NAME) + 1;
  appName = malloc(len);
  snprintf(appName, len, APP_NAME);
  logMessage(1, debug_mode, app, appName, thread, msg);
  free(app);
  free(appName);
}

/**
 * @brief Write a message to the log file with timestamp and process ID.
 * 
 * This function writes a message to the log file with timestamp and process ID.
 * The log file is located in LOG_DIR directory with the format APP-YYYY-MM-DD.log.
 *
 * @param msg The message to be written to the log file.
 *
 * @return void
 *
 * @see advanced_log() 
 * @see init_log() to initialize the log file directory.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void log_message(const char *msg) {
  advanced_log( 0, "", msg);
}

/**
 * @brief Write debug log messages to a file with a timestamp and process ID
 * 
 * This function writes a debug log message to a file named "APP-YYYY-MM-DD-debug.log"
 * located in the directory specified by the LOG_DIR macro. The log message includes a 
 * timestamp and process ID.
 * 
 * @param thread The name of the thread writing the log message.
 * @param msg The debug log message to be written to the log file.
 * 
 * @return void
 * 
 * @see advanced_log() 
 * @see init_log() to initialize the log file directory.
 * 
 * @date 2023-06-03
 * @author Cloudgen Wong
 */
void log_message_w_thread(const char *thread, const char *msg) {
  advanced_log( 0, thread, msg);
}

/**
 * @brief Write debug log messages to a file with a timestamp and process ID
 * 
 * This function writes a debug log message to a file named "APP-YYYY-MM-DD-debug.log"
 * located in the directory specified by the LOG_DIR macro. The log message includes a 
 * timestamp and process ID.
 * 
 * @param msg The debug log message to be written to the log file.
 * @param debug_mode A flag indicating whether or not debug mode is enabled.
 * 
 * @return void
 * 
 * @see advanced_log() 
 * @see init_log() to initialize the log file directory.
 * 
 * @date 2023-06-06
 * @author Cloudgen Wong
 */
void debug_log_message(int debug_mode, const char *msg) {
  if (!debug_mode) return;
  advanced_log( debug_mode, "", msg);
}

/**
 * @brief Write debug log messages to a file with a timestamp, process ID, and thread ID.
 * 
 * This function writes a debug log message to a file named "APP-YYYY-MM-DD-debug.log"
 * located in the directory specified by the LOG_DIR macro. The log message includes a 
 * timestamp, process ID, and thread ID.
 * 
 * @param debug_mode A flag indicating whether or not debug mode is enabled.
 * @param thread A string representing the thread ID.
 * @param msg The debug log message to be written to the log file.
 * 
 * @return void
 * 
 * @see advanced_log() 
 * @see init_log() to initialize the log file directory.
 * 
 * @date 2023-06-03
 * @author Cloudgen Wong
 */
void debug_log_message_w_thread(int debug_mode, const char *thread, const char *msg) {
  if (!debug_mode) return;
  advanced_log( debug_mode, thread, msg);
}
