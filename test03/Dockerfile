# host /etc/resolv.conf --> nameserver 8.8.8.8
# docker build --network host -t sqlite-debian-golang .

FROM golang:latest as builder
RUN useradd -m -u 1000 user
USER user
WORKDIR /tmp

# docker run --rm -v `pwd`:/tmp -t sqlite-debian-golang make static-binary
