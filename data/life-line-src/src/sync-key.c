#include "copy-if-not-exists.h"
#include "set-file-permission.h"
#include "sync-key.h"

/**
 * @file sync-key.c
 * @brief Synchronize key files between different locations.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */

/**
 * @brief Synchronize key files between different locations.
 * 
 * This function synchronizes key files between different locations by copying them if they do not exist in the destination.
 * The key files include the private and public keys for both data and root directories.
 *
 * @param dataPriKey The path to the data private key file.
 * @param dataPubKey The path to the data public key file.
 * @param rootPriKey The path to the root private key file.
 * @param rootPubKey The path to the root public key file.
 * @param thread_name The name of the thread.
 * @param debug_mode The debug mode indicator.
 *
 * @return void
 *
 * @details The function first copies the data private key file to the root private key file location.
 * It then sets the file permissions of the root private key file to 0600 (read and write by owner only).
 * If the data private key file was successfully copied, it checks if the root private key file was copied.
 * If not, it copies the root public key file to the data public key file location.
 * Debug log messages are generated and displayed using the provided thread name and debug mode.
 *
 * @note This function requires the following include files:
 * @note None.
 *
 * @see copy_if_not_exist() to copy a file if it does not exist in the destination.
 * @see setFilePermissions() to set file permissions.
 *
 * @author Cloudgen Wong
 * @date 2023-06-06
 */
void syncKey(const char* dataPriKey, const char* dataPubKey, const char* rootPriKey, const char* rootPubKey, const char* thread_name, int debug_mode){
  copy_if_not_exist(dataPriKey, rootPriKey, thread_name, debug_mode);
  setFilePermissions(rootPriKey, 0600, thread_name, debug_mode);
  if (copy_if_not_exist(rootPriKey, dataPriKey, thread_name, debug_mode)) {
    copy_if_not_exist(rootPubKey, dataPubKey, thread_name, debug_mode);
  }
}