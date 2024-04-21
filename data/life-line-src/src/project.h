#ifndef PROJECT_H
#define PROJECT_H

/**
 * @file project.h
 * @brief Keeps major constant used in this project
 *
 * @author Cloudgen Wong
 * @date 2024-4-16
 */

/* Required by log-message.c */
#define APP "life-line"
#define APP_NAME "LifeLine"
#define APP_VERSION "16.19"
#define DATA_ROOT "/data/"
#define DATA_LOG DATA_ROOT "doc-root/log/"
#define LOG_DIR DATA_LOG APP

/* Required by main */
#define ROOT "/root/"
#define ROOT_SSH ROOT ".ssh/"
#define ROOT_DATA ROOT ".data/"
#define DATA_SSH DATA_ROOT ".ssh/"
#define DATA_PRIVATE_KEY DATA_SSH "id_rsa"
#define DATA_PUBLIC_KEY DATA_SSH "id_rsa.pub"
#define ROOT_PRIVATE_KEY ROOT_SSH "id_rsa"
#define ROOT_PUBLIC_KEY ROOT_SSH "id_rsa.pub"
#define TUNNEL_DIR DATA_ROOT "tunnel/"
#define TUNNEL_CONF TUNNEL_DIR "tunnel.conf"
#define TUNNEL_CMD1 "/usr/bin/check-tunnel"
#define TUNNEL_CMD2 "/usr/local/bin/check-tunnel"
#define TUNNEL_CMD3 "/usr/bin/start-tunnel"
#define TUNNEL_CMD4 "/usr/local/bin/start-tunnel"

#endif /* PROJECT_H */
