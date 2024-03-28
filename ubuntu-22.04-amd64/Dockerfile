FROM ubuntu:22.04
LABEL maintainer="Cloudgen Wong <cloudgen.wong@beampluslab.io>" \
   architecture="amd64/x86_64"

ADD target/usr.tar.gz /

WORKDIR /data
VOLUME ["/data"]
ENTRYPOINT ["/usr/bin/life-line"]
