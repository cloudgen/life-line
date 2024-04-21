#include "copy-folder.h"
#include "copy-if-not-exists.h"
#include "log-message.h"

/**
 * @file copy-folder.c
 * @brief Copy the contents of a folder to another folder.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

/**
 * @brief Copy the contents of a folder to another folder.
 * 
 * This function recursively copies the contents of a source folder to a destination folder.
 * It preserves the directory structure and copies both directories and files.
 * 
 * @param sourceFolder The path to the source folder.
 * @param destinationFolder The path to the destination folder.
 * @param thread_name The name of the thread invoking the function.
 * @param debug_mode The debug mode flag.
 * 
 * @return void
 * 
 * @details The function opens the source folder and creates the destination folder if it does not exist.
 * It then iterates through the entries in the source folder. For each entry, if it is a directory,
 * the function recursively calls itself with the corresponding subfolders. If it is a file, it attempts
 * to move it to the destination folder using the `rename()` function. If the move fails, it falls back
 * to copying the file using the `copy_if_not_exist()` function. If any errors occur during the process,
 * they are logged to the log file with the provided thread name.
 * 
 * @note This function requires the following include files:
 * @note #include <stdio.h> // for FILE, snprintf
 * @note #include <stdlib.h> // for malloc, free
 * @note #include <dirent.h> // for DIR, struct dirent, opendir, readdir, closedir
 * @note #include <sys/stat.h> // for struct stat, stat
 * @note #include <limits.h> // for PATH_MAX
 *
 * @see copy_if_not_exist() to copy a file if it does not exist in the destination folder.
 * @see log_message_w_thread() to log error messages to the log file.
 * 
 * @date 2023-06-06
 * @author Cloudgen Wong
 */
void copyFolder(const char* sourceFolder, const char* destinationFolder, const char* thread_name, int debug_mode) {
  DIR* dir;
  struct dirent* entry;
  char *s = NULL;
  int len;

  // Open the source folder
  dir = opendir(sourceFolder);
  if (!dir) {
    len = snprintf(NULL, 0, "Failed to open source folder: %s", sourceFolder) + 1;
    s = malloc(len);
    snprintf(s, len, "Failed to open source folder: %s", sourceFolder);
    log_message_w_thread(thread_name, s);
    free(s);
    return;
  }

  // Create the destination folder if it doesn't exist
  struct stat st;
  if (stat(destinationFolder, &st) == -1) {
    if (mkdir(destinationFolder, 0755) == -1) {
      len = snprintf(NULL, 0, "Failed to create destination folder: %s", destinationFolder) + 1;
      s = malloc(len);
      snprintf(s, len, "Failed to create destination folder: %s", destinationFolder);
      log_message_w_thread(thread_name, s);
      free(s);
      closedir(dir);
      return;
    }
  }

  // Iterate through the entries in the source folder
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    // Construct the paths for the current entry
    char sourcePath[PATH_MAX];
    snprintf(sourcePath, sizeof(sourcePath), "%s/%s", sourceFolder, entry->d_name);

    char destinationPath[PATH_MAX];
    snprintf(destinationPath, sizeof(destinationPath), "%s/%s", destinationFolder, entry->d_name);

    // Check if the current entry is a directory
    if (entry->d_type == DT_DIR) {
      // Recursively copy the subfolder
      copyFolder(sourcePath, destinationPath, thread_name, debug_mode);
    } else {
      // Copy the file
      if (rename(sourcePath, destinationPath) == -1) {
        // Failed to move, fallback to file copy
        copy_if_not_exist(sourcePath, destinationPath, thread_name, debug_mode);
      }
    }
  }
  closedir(dir);
}