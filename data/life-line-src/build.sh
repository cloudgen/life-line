#!/bin/sh

# @author Cloudgen Wong
# @date 2023-11-23

safe_rm() {
    if [ -f /usr/bin/origin-rm ]; then
        RM=/usr/bin/origin-rm
    elif [ -f /usr/bin/rm ]; then
	RM=/usr/bin/rm
    else
        RM=/bin/rm
    fi
    SW=`echo $1| sed 's/^ *| *$//g'`
    CH=`echo $SW| sed 's/^\-.*/-/g'`
    if [ "${SW}" = "-restore" ]; then
        restore
        exit 0
    elif [ "${CH}" = "-" ]; then
        trimmed=`echo $2| sed 's/^ *| *$//g'`
        CH2=`echo $SW| sed 's/^\-.*/-/g'`
        if [ ! -z "$3" ] && [ "${CH2}" = "-" ]; then
            trimmed=`echo $3| sed 's/^ *| *$//g'`
            target_list="${trimmed##*( )}"
        else
            SW2=""
            target_list="${trimmed##*( )}"
        fi
        for target in ${target_list}; do
            CH_T=`echo $target | sed 's:/usr/:/:g' | sed 's:./$::g'| sed 's:[^/]*$::g'`
            if [ "${target}" = "/" ] || [ "${target}" = "/usr/bin" ] \
                || [ "${target}" = "/usr/bin/" ]  \
                || [ "${CH_T}" = "/" ]; then
                printf "»build.sh:\n  Sorry I can't rm ${SW} ${SW2} ${target} ${CH_T}\n"
            else
                printf "»build.sh:\n"
                $RM "${SW}" "${SW2}" "${target}"
            fi
        done
    else
        trimmed=`echo $1| sed 's/^ *| *$//g'`
        target="${trimmed##*( )}"
        if [ -f "${target}" ]; then
            printf "»build.sh:\n  ${target} Found!\n"
            /usr/bin/unlink "${target}"
        else
            if [ -z "${target}" ]; then
                printf "»build.sh:\n  Please specify target\n"
                exit 0
            else
                printf "»build.sh:\n  File not exists: ${target}\n"
            fi
        fi
    fi
    printf "  rm ${1} ${2} ${3} ${4}\n"
}

os() {
    OS=$(cat /etc/os-release | grep PRETTY_NAME | cut -d\" -f2| cut -d\  -f1)
    echo $OS
}

build_main() {
    FNAME=life-line
    TARGET_DIR=target
    TARGET=${TARGET_DIR}/${FNAME}
    EXPORT_DIR=export
    EXPORT_FILE=${FNAME}.tar.gz
    EXPORT=${EXPORT_DIR}/${EXPORT_FILE}

    # create the target directory if it doesn't exist
    mkdir -p ${TARGET_DIR}

    # clean the target folder for any previous compilation
    safe_rm -rf ${TARGET}

    gcc -Wall -Werror \
        src/check-tunnel.c \
        src/copy-folder.c \
        src/copy-if-not-exists.c \
        src/display-signal-message.c \
        src/fix-docroot.c \
        src/get-file-permission.c \
        src/handle-exit.c \
        src/life-line.c \
        src/log-message.c \
        src/main.c \
        src/make-directory.c \
        src/remove-old-log.c \
        src/set-file-permission.c \
        src/sync-data-folder.c \
        src/sync-key.c \
        -o ${TARGET}

    if [ $? -ne 0 ]; then
        echo "Build failed. Please check the error messages above."
        exit 1
    fi

    # Make the binary executable
    chmod +x ${TARGET}

    if [ "$1" = "install" ]; then
        cp ${TARGET} /usr/bin/
        echo "Build successful! Please run '${FNAME}'"
    elif [ "$1" = clean ]; then
        safe_rm -rf ${TARGET_DIR}/*
        echo "Folder ${TARGET_DIR} has been cleared!"
    elif [ "$1" = "test" ]; then
        # Set the necessary variables
        tests/test.sh ${TARGET} tests/test-cases.txt
    elif [ "$1" = "compress" ]; then
        # create the target directory if it doesn't exist
        mkdir -p ${EXPORT_DIR}

        # clean the target folder for any previous compilation
        safe_rm -rf ${EXPORT}
        # Compress binary to "export" folder
        cd ${TARGET_DIR}
        tar -cvf ${EXPORT_FILE} ${FNAME}
        mv ${EXPORT_FILE} ../${EXPORT_DIR}
    else
        echo "Build successful! Please run '${TARGET}'"
    fi
}

build_main "$1"
