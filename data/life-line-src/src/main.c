#include <libgen.h>       /* for basename */
#include <stdio.h>        /* for fprintf, stderr */ 
#include "fix-docroot.h"
#include "handle-exit.h"
#include "life-line.h"
#include "log-message.h"
#include "make-directory.h"
#include "project.h"
#include "remove-old-log.h"
#include "sync-key.h"

/**
 * @brief LifeLine - Prevents Docker container exit and manages SSH keys for the root account.
 * 
 * LifeLine is a program designed to ensure the continuous operation of Docker containers
 * by preventing them from exiting and maintaining a useful set of SSH keys for the root account.
 * 
 * The main function creates a directory to be monitored and enters an infinite loop to check for changes
 * to the directory. Each iteration of the loop is logged using the `log_message` function, and the program
 * gracefully exits when a SIGINT or SIGTERM signal is received.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * 
 * @return int Returns 0 if the program runs successfully.
 * 
 * @details The function initializes the log, creates the root SSH folder, sets up the signal handler for graceful exit,
 * and starts the life line loop. It also checks for command-line arguments to enable debug mode or perform specific actions
 * such as printing the version or generating a simple log.
 * 
 * @note This function requires the following include files:
 * @note #include <stdio.h> // for fprintf, stderr
 * 
 * @see handle_exit - Signal handler function
 * @see make_directory - Function to create a directory
 * @see remove_old_logs - Function to remove old logs from a directory
 * 
 * @author Cloudgen Wong
 * @date 2024-04-19
 */
int main(int argc, char *argv[]) {
  char *thread_name = "Thread_main";
  int debug_mode = 0;
  char *me = basename(argv[0]);
  if((strcmp(me, "ll-log-msg") == 0) || (strcmp(me, "ll-log-file") == 0) || 
    (strcmp(me, "ll-pid-file") == 0) || (strcmp(me, "ll-remove-old-log") == 0) || 
    (strcmp(me, "ll-sync-key") == 0) || (strcmp(me, "ll-fix-docroot") == 0)) {
    init_log_appName(debug_mode, "", me);
  } else {
    init_log(thread_name);
  }
  if(strcmp(me, "ll-log-msg") == 0) {
    if(argc == 3) {
      advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
      simple_log(argv[1], argv[2]);
      advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
    } else if (argc == 4) {
      int pid = atoi(argv[1]);
      advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
      simple_log_with_pid(pid, argv[2], argv[3]);
      advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
    } else if(argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0 ||  strcmp(argv[1], "version") == 0)) {
      advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
      printf("%s(%s) version:%s\n", me, APP_NAME, APP_VERSION );
      advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
    } else {
      advanced_log_appname(debug_mode, "", me,"====== State: .*ARGU_CHECKING* -> *END*...... ======");
    }
    return 0;
  } else if(strcmp(me, "ll-log-file") == 0) {
    if(argc == 2) {
      if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0 ||  strcmp(argv[1], "version") == 0) {
        advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("%s(%s) version:%s\n", me, APP_NAME, APP_VERSION );
        advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
      } else {
        char *filename=logFilenameWithTimeStamp(debug_mode, prepareLogDir(DATA_LOG, argv[1]), argv[1]);
        advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("%s\n", filename );
        free(filename);
        advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
      }
    } else {
      advanced_log_appname(debug_mode, "", me,"====== State: .*ARGU_CHECKING* -> *END*...... ======");
    }
    return 0;
  } else if(strcmp(me, "ll-pid-file") == 0) {
    if(argc == 2) {
      if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0 ||  strcmp(argv[1], "version") == 0) {
        advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("%s(%s) version:%s\n", me, APP_NAME, APP_VERSION );
        advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
      } else {
        advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("/var/run/%s.pid\n", argv[1] );
        advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
      }
    } else {
      advanced_log_appname(debug_mode, "", me,"====== State: .*ARGU_CHECKING* -> *END*...... ======");
    }
    return 0;
  } else if(strcmp(me, "ll-remove-old-log") == 0) {
    if(argc == 2) {
      if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0 ||  strcmp(argv[1], "version") == 0) {
        advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("%s(%s) version:%s\n", me, APP_NAME, APP_VERSION );
        advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
        return 0;
      } else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0 ||  strcmp(argv[1], "swvyf") == 0) {
        debug_mode = 1;
      }
    }
    advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
    remove_old_logs_with_debug(DATA_LOG, ".log", thread_name, debug_mode);
    advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
    return 0;
  } else if(strcmp(me, "ll-sync-key") == 0) {
    if(argc == 2) {
      if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0 ||  strcmp(argv[1], "version") == 0) {
        advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("%s(%s) version:%s\n", me, APP_NAME, APP_VERSION );
        advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
        return 0;
      } else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0 ||  strcmp(argv[1], "swvyf") == 0) {
        debug_mode = 1;
      }
    } 
    advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
    syncKey(DATA_PRIVATE_KEY, DATA_PUBLIC_KEY, ROOT_PRIVATE_KEY, ROOT_PUBLIC_KEY, thread_name, debug_mode);
    advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
    return 0;    
  } else if(strcmp(me, "ll-fix-docroot") == 0) {
    if(argc == 2) {
      if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0 ||  strcmp(argv[1], "version") == 0) {
        advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("%s(%s) version:%s\n", me, APP_NAME, APP_VERSION );
        advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
        return 0;
      } else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0 ||  strcmp(argv[1], "swvyf") == 0) {
        debug_mode = 1;
      }
    } 
    advanced_log_appname(debug_mode, "", me,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
    fixDocRoot(thread_name, debug_mode);
    advanced_log_appname(debug_mode, "", me,"====== State: .*RUNNING* -> *END*............ ======");
    return 0;    
  } else {
    if (argc == 2) {
      if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0 ||  strcmp(argv[1], "version") == 0) {
        advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("%s(%s) version:%s\n", APP_NAME, APP_NAME, APP_VERSION );
        advanced_log_appname(debug_mode, "", APP_NAME,"====== State: .*RUNNING* -> *END*............ ======");
        return 0;    
      } else if(strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "-F") == 0 || strcmp(argv[1], "--debug") == 0 || strcmp(argv[1], "debug") == 0) {
        debug_mode = 1;
      } else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "help") == 0) {
        advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        printf("life-line [-dFhlosv] [--][debug|help|log|logfile|shortlink|version]\n");
        advanced_log_appname(debug_mode, "", APP_NAME,"====== State: .*RUNNING* -> *END*............ ======");
        return 0;    
      } else if(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--shortlinnk") == 0 || strcmp(argv[1], "shortlink") == 0) {
        advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        lifeLifeShortLink(thread_name, 1);
        printf("Shortlinks: ll-log-file, ll-pid-file,. ll-log-msg, ll-remove-old-log, ll-sync-key, ll-fix-docroot\n    have been ..Created..\n");
        advanced_log_appname(debug_mode, "", APP_NAME,"====== State: .*RUNNING* -> *END*............ ======");
        return 0;    
      }
    }else if (argc == 3){
      if (strcmp(argv[1], "-o") == 0 || strcmp(argv[1], "--logfile") == 0 ||  strcmp(argv[1], "logfile") == 0) {
        advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
        char *filename=logFilenameWithTimeStamp(debug_mode, prepareLogDir(DATA_LOG, argv[2]), argv[2]);
        printf("%s\n", filename );
        free(filename);
        advanced_log_appname(debug_mode, "", APP_NAME,"====== State: .*RUNNING* -> *END*............ ======");
        return 0;    
      }
    } else if (argc == 4 && (strcmp(argv[1], "log") == 0 || strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--log") == 0)) {
      advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
      simple_log(argv[2], argv[3]);
      advanced_log_appname(debug_mode, "", APP_NAME,"====== State: .*RUNNING* -> *END*............ ======");
      return 0;    
    } else if (argc == 5 && (strcmp(argv[1], "log") == 0 || strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "--log") == 0)) {
      int pid = atoi(argv[2]);
      advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
      simple_log_with_pid(pid, argv[3], argv[4]);
      advanced_log_appname(debug_mode, "", APP_NAME,"====== State: .*RUNNING* -> *END*............ ======");
      return 0;    
    }
    advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*ARGU_CHECKING* -> *RUNNING*.. ------");
    lifeLifeShortLink(thread_name, debug_mode);
    if (make_directory(ROOT_SSH) != 0) {
      log_message_w_thread( thread_name, "Creating folder: " ROOT_SSH " ..Failed..");
    }
    signal_exit();
    life_line(thread_name, debug_mode);
    if (argc == 1) {
      advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*RUNNING* -> *MAIN_LOOP*...... ------");
      life_line_loop(thread_name, debug_mode);
    } else if (argc == 2 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "-F") == 0)) {
      advanced_log_appname(debug_mode, "", APP_NAME,"------ State: .*RUNNING* -> *MAIN_LOOP*...... ------");
      life_line_loop(thread_name, debug_mode);
    } else {
      advanced_log_appname(debug_mode, "", APP_NAME,"====== State: .*RUNNING* -> *END*............ ======");
    }
  }
  return 0;
}
