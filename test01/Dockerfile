# host /etc/resolv.conf --> nameserver 8.8.8.8
# docker build --network host -t sqlite-debian-cpp .

FROM gcc as builder

RUN apt-get update
RUN apt-get -y install sqlite3 libboost-filesystem-dev libvsqlitepp-dev

RUN useradd -m -u 1000 user
USER user

WORKDIR /tmp

# docker run --rm -v `pwd`:/tmp -t sqlite-debian-cpp make static-binary 
