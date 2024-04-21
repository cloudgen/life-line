#include "copy-folder.h"
#include "log-message.h"
#include "project.h"
#include "sync-data-folder.h"

/**
 * @file sync-data-folder.c
 * @brief Synchronize the data folder by copying subfolders from the root data folder to the destination.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

/**
 * @brief Check if a folder exists at the specified path.
 * 
 * This function checks if a folder exists at the given folderPath.
 * It returns true if the folder exists and false otherwise.
 *
 * @param folderPath The path of the folder to check.
 *
 * @return bool - true if the folder exists, false otherwise.
 *
 * @details The function uses the `stat` function from the sys/stat.h header file
 * to retrieve information about the file or directory at the specified path.
 * If the `stat` function call succeeds and the retrieved information indicates
 * that the path corresponds to a directory, the function returns true.
 * Otherwise, it returns false.
 *
 * @note This function requires the following include files:
 * @note #include <sys/stat.h> // for struct stat, stat, S_ISDIR
 * @note #include <stdbool.h> // true, false
 *
 * @see None.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
bool folderExists(const char* folderPath) {
  struct stat st;
  if (stat(folderPath, &st) == 0 && S_ISDIR(st.st_mode))
    return true;
  return false;
}

/**
 * @brief Synchronize the data folder by copying subfolders from the root data folder to the destination.
 * 
 * This function synchronizes the data folder by copying subfolders from the root data folder to the destination folder.
 * It returns 0 if the synchronization is successful.
 *
 * @param thread_name The name of the thread.
 * @param debug_mode The debug mode indicator.
 *
 * @return int - 0 if the synchronization is successful, 1 otherwise.
 *
 * @details The function opens the root data folder and iterates through its entries.
 * For each subfolder entry, it constructs the source and destination paths,
 * and then checks if the subfolder already exists in the destination.
 * If the subfolder doesn't exist in the destination, it copies the subfolder from the source to the destination.
 * During the copying process, debug log messages are generated and displayed using the provided thread name and debug mode.
 * After the synchronization is completed, a log message is written to indicate the success.
 *
 * @note This function requires the following include files:
 * @note #include <stdio.h> // for FILE, snprintf
 * @note #include <stdlib.h> // for malloc, free
 * @note #include <dirent.h> // for DIR, struct dirent, opendir, readdir, closedir
 * @note #include <limits.h> // for PATH_MAX
 * @note #include <string.h> // for strcmp
 *
 * @see folderExists() to check if a folder exists.
 * @see copyFolder() to copy a folder from the source to the destination.
 * @see debug_log_message_w_thread() to log debug messages with thread name.
 * @see log_message_w_thread() to write log messages with thread name.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
int sync_data_folder(const char* thread_name, int debug_mode) {
  DIR* dir;
  struct dirent* entry;
  int len;
  char *s;
  // Open the root data folder
  dir = opendir(ROOT_DATA);
  if (!dir) {
    debug_log_message_w_thread(debug_mode, thread_name, "Open root data folder: " ROOT_DATA " ..Failed..");
    return 1;
  } 
  int folder_copied = 0;
  // Iterate through the entries in the root data folder
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type != DT_DIR) {
      continue;
    }
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }
    // Construct the paths for the current entry
    char sourceFolder[PATH_MAX];
    snprintf(sourceFolder, sizeof(sourceFolder), ROOT_DATA "%s", entry->d_name);
    char destinationFolder[PATH_MAX];
    snprintf(destinationFolder, sizeof(destinationFolder), DATA_ROOT "%s", entry->d_name);

    // Copy the subfolder if it doesn't exist in the destination
    if (!folderExists(destinationFolder)) {
      copyFolder(sourceFolder, destinationFolder, thread_name, debug_mode);
      len = snprintf(NULL, 0, "Folder copied: from %s to %s ..Success..", sourceFolder, destinationFolder);
      s = malloc(len + 1);
      snprintf(s, len + 1, "Folder copied: from %s to %s ..Success..", sourceFolder, destinationFolder);
      debug_log_message_w_thread(debug_mode, thread_name, s);
      folder_copied = 1;
      free(s);
    } else {
      len = snprintf(NULL, 0, "Destination folder: %s ..Exists..", destinationFolder);
      s = malloc(len + 1);
      snprintf(s, len + 1, "Destination folder: %s ..Exists..", destinationFolder);
      debug_log_message_w_thread(debug_mode, thread_name, s);
      free(s);
    }
  }
  closedir(dir);
  if (folder_copied ) {
    log_message_w_thread(thread_name,"Data folder synchronized.");
  }
  return 0;
}