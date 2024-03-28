FROM ubuntu:23.04
LABEL maintainer="Cloudgen Wong <cloudgen.wong@beampluslab.io>" \
   architecture="arm64v8/aarch64"

ADD target/usr.tar.gz /

WORKDIR /data
VOLUME ["/data"]
ENTRYPOINT ["/usr/bin/life-line"]
