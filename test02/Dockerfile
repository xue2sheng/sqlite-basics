# host /etc/resolv.conf --> nameserver 8.8.8.8
# docker build --network host -t sqlite-debian-rust .

FROM rust as builder

RUN apt-get update
RUN apt-get -y install musl-tools

RUN useradd -m -u 1000 user
USER user

RUN rustup target add x86_64-unknown-linux-musl

WORKDIR /tmp

# docker run --rm -v `pwd`:/tmp -t sqlite-debian-rust make static-binary
