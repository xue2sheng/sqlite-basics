# sqlite-basics

Fooling around with different languages about sqlite basics. The intention is to learn their different strong and weak points when it comes down to development and  deployment.

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

Trying to generate 'static' binaries will depend on what libraries you're using and what operative system you should support. For example, if your Linux distro doesn't install all 'static' libraries by default, i.e. Archlinux got only boost static libraries, you should provide the rest. 

In other words, download the missing static libraries source code, statically build them following their specific instruction, i.e. [sqlite3](https://github.com/sqlite/sqlite) or [vsqlite++](https://github.com/vinzenz/vsqlite--), and then proceed to build our 'static' binary.

	make additional
	g++ -L./static -L/usr/lib main.cpp -static -lvsqlitepp -lsqlite3 -lboost_filesystem -o test01_static && ./test01_static
	/usr/bin/ld: ./static/libsqlite3.a(sqlite3.o): in function `unixDlOpen':
	/home/user/Code/sqlite/static/sqlite/build/sqlite3.c:42061: warning: Using 'dlopen' in statically linked applications requires at runtime the shared libraries from the glibc version used for linking
	word='helloworld' value=20
	word='archlinux' value=30

	ldd ./test01_static 
	not a dynamic executable

	ls -larth ./test01_static 
	-rwxr-xr-x 1 user users 8.6M Aug 21 03:10 ./test01_static

But the cleanest approach for 'static' binaries would be to use a proper Docker, where boost, sqlite and vsqlite++ are dealt with. Besides, you might avoid ugly 'statically' built dependencies, i.e. [ldopen](https://wiki.musl-libc.org/functional-differences-from-glibc.html#Lazy-bindings), that way. Remember you might have let your docker container to access Internet to download additional packages:

	# host /etc/resolv.conf --> nameserver 8.8.8.8
	docker build --network host -t sqlite-debian-cpp .
	docker run --rm -v `pwd`:/tmp -t sqlite-debian-cpp make static-binary

Take into account that you might want to modify what 'user' is used at that Dockerfile.

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

Although it doesn't make too much sense for this example, here you are some basic Dockerfile to build statically that binary. Remember you might have let your docker container to access Internet to download additional packages:

	# host /etc/resolv.conf --> nameserver 8.8.8.8
	docker build --network host -t sqlite-debian-rust .
	docker run --rm -v `pwd`:/tmp -t sqlite-debian-rust make static-binary

Take into account that you might want to modify what 'user' is used at that Dockerfile.

## [Go](test03/)

If you don't want to depend on C/C++ compilers and make your life easy when it comes down to cross-compiling from other systems, i.e. Windows, Go might be a clever option. Take into account Go got its grabage collector to speed development up, but implying bigger binaries just for that fact.

[Code Example](test03/main.go)

As expected, there is a balance between dependencies and size:

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

There is some example of a Dockerfile to build a static linux binary. Remember you might have let your docker container to access Internet to download additional packages:

	# host /etc/resolv.conf --> nameserver 8.8.8.8
	docker build --network host -t sqlite-debian-golang .
	docker run --rm -v `pwd`:/tmp -t sqlite-debian-golang make static-binary

Take into account that you might want to modify what 'user' is used at that Dockerfile.

## Conclusion

For fast development, when your team doesn't have too much time or willingmess to learn new languages, and you're forced to use Windows as daily driver although your target is Linux, Go might be the first option to consider. Easy to learn and no too cumbersome dependencies on C/C++ toolchains, especially for cross-compilations.

If your team can invest the time on learning complex languages and developing at a bit slower pace, Rust could be your next candidate. Take into account its learning curve is not a joke and its dependency on a C toolchain might be a limitaton for some company policies. Being a "novelty" doesn't help on a typical corporate Windows workplace although developers love this language and its tooling. 

In case your product requires fast and small binaries, C++ might be the best option to get your bosses on board. But only provided you're working with containers and/or allowed to invest time on DevOps. Getting your toolchain to produce small static binaries to be easily deployed might imply to use the latest versions of compilers and dependencies and investigations on your Linux boxes. Having avaible updated Docker images should spare you a lot of time and suffering.
 
