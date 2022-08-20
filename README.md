# sqlite-basics

Fooling around with different languages about sqlite basics. The intention is to learn their differnt strong and weak points when it comes down to development and  deployment.

Therefore, we will just use the "hello world" sqlite at [Achlinux wiki](https://wiki.archlinux.org/title/SQLite):

       create table tblone(one varchar(10), two smallint);
       insert into tblone values('helloworld',20);
       insert into tblone values('archlinux', 30);

## [C++](test01/)

Taking for granted your daily driver is Linux, i.e. Archlinux, is very easy to have installed your dependencies with the standard package manager, i.e. pacman, and develop in the usual way.

[Code Example](test01/main.cpp)

As expected, the more dependencies your binary has, the smaller it is:

       make
	g++ -lvsqlitepp main.cpp -o test01 && ./test01
	word='helloworld' value=20
	word='archlinux' value=30

       ldd ./test01
	linux-vdso.so.1 => linux-vdso.so.1 (0x00007ffd73fb0000)
	libvsqlitepp.so.3 => /usr/lib/libvsqlitepp.so.3 (0x00007fa22b224000)
	libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x00007fa22ae00000)
	libm.so.6 => /usr/lib/libm.so.6 (0x00007fa22b13c000)
	libgcc_s.so.1 => /usr/lib/libgcc_s.so.1 (0x00007fa22b11c000)
	libc.so.6 => /usr/lib/libc.so.6 (0x00007fa22ac19000)
	libsqlite3.so.0 => /usr/lib/libsqlite3.so.0 (0x00007fa22aace000)
	/lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007fa22b293000)

       test01 ls -larth ./test01
        -rwxr-xr-x 1 user users 30K Aug 20 21:50 ./test01*

Trying to generate 'static' binaries will depend on what libraries you're using and what operative system you should support.

## [Rust](test02/)

Provided you have access to a C compiler on your system, working with Rust will allow you to generate 'static' binaries in an easier way than before.

[Code Example](test02/src/main.rs)

As expected, the fewer dependencies your binary has, the bigger it is:

       make
        RUSTFLAGS='-C target-feature=+crt-static' cargo run --target=x86_64-unknown-linux-musl --release -q
	Item { name: "helloworld", value: 20 }
	Item { name: "archlinux", value: 30 }

       ldd target/x86_64-unknown-linux-musl/release/test02
	statically linked

       ls -larth target/x86_64-unknown-linux-musl/release/test02
	-rwxr-xr-x 2 user users 5.7M Aug 20 20:56 target/x86_64-unknown-linux-musl/release/test02*

## [Go](test03/)

If you don't want to depend on C/C++ compilers and make your life easy when it comes down to cross-compiling from other systems, i.e. Windows, Go might be a clever option. Take into account Go got its grabage collector to speed development but implying bigger binaries.

[Code Example](test03/main.go)

As expected, there is balance between dependencies and size:

       make
	go build -a -ldflags '-s -w' -o test03 && ./test03
	name='helloworld' value=20
	name='archlinux' value=30

       ldd ./test03
	linux-vdso.so.1 => linux-vdso.so.1 (0x00007fff963e0000)
	libc.so.6 => /usr/lib/libc.so.6 (0x00007ffba4690000)
	/lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007ffba48b4000)

       ls -larth ./test03
	-rwxr-xr-x 1 user users 3.4M Aug 20 23:36 ./test03*
