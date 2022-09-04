# host /etc/resolv.conf --> nameserver 8.8.8.8
# docker build --network host -t sqlite-debian .

FROM gcc as builder

RUN apt-get update
RUN apt-get -y install sqlite3 libboost-filesystem-dev libvsqlitepp-dev

COPY static/ /tmp/static/
WORKDIR /tmp

COPY Makefile . 
COPY main.cpp . 
COPY test01.db . 

# docker run --rm -v `pwd`:/tmp -t sqlite-debian make static-binary 
