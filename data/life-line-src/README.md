# App Release:

Release Date: 11-17-2023

Version: 11.17

MD5SUM: 4292cb0a00e30ce33a419e2554aa9467

# life-line Command for Docker

This project provides a command line tool called "life-line" which can be installed in any Docker image as the last command of an entrypoint. The purpose of this command is to ensure that the Docker container does not exit after it finishes executing all the commands specified in the entrypoint. It also keeps track of the minimum activity by writing a log message every 300 seconds. The logs older than 7 days are automatically removed.

## Usage

To use this command, simply include it as the last command in your Docker entrypoint. For example:

~~~
ENTRYPOINT ["mycommand", "arg1", "arg2", "&&", "life-line"]
~~~

This will ensure that the Docker container stays alive after mycommand finishes executing.

## Private Key
You should intall your private in /data/.ssh/ and rename as /data/.ssh/id_rsa 

## Tunnel Configuration
Here is an example of the /data/tunnel/tunnel.conf for ubuntu
~~~
#!/bin/bash

export TUNNEL_NAME=dev-00
export LOCAL_PORT=80
export REMOTE_PORT=2000
export REMOTE_SERVER=console.beampluslab.io
export WORKING_DIRECTORY=/etc/${TUNNEL_NAME}
export ME=dev-00
export TMP_DIRECTORY=/data/tunnel/${ME}
mkdir -p ${TMP_DIRECTORY}
export PID_FILE=/var/run/${TUNNEL_NAME}.pid
export TUNNEL_SETTING=":${REMOTE_PORT}:localhost:${LOCAL_PORT}"
export CHECK_TUNNEL="sudo netstat -peanut 2>/dev/null|grep :$REMOTE_PORT|grep LISTEN|awk '{print \$9}'|grep -v -|head -n 1| cut -d '/' -f 1"
export CHECK_FILE=${TMP_DIRECTORY}/check-result

~~~
The following is an example of the /data/tunnel/tunnel.conf for alpine:
~~~
#!/bin/sh

export TUNNEL_NAME=ipfs-server-03
export LOCAL_PORT=80
export REMOTE_PORT=8389
export REMOTE_SERVER=git.theauthority.asia
~~~

## Implementation

The main function of the program creates a directory to be monitored and enters an infinite loop to check for changes to the directory. It logs each iteration of the loop using the log_message function, and exits gracefully when a SIGINT or SIGTERM signal is received.

## Docket exposed folder

The daemon program expected to keep operation data under folder: /data

## Credits

This project was created by Cloudgen Wong. For any questions or concerns, please contact the author at info@leolio.page
