all: main.cpp test01.db
	g++ -lvsqlitepp main.cpp -o test01 && ./test01
additional:
	g++ -L./static -L/usr/lib main.cpp -static -lvsqlitepp -lsqlite3 -lboost_filesystem -o test01_static && ./test01_static
static-binary: main.cpp 
	mkdir -p ~/build
	cp main.cpp ~/build
	cp -r static ~/build/static
	rm -rf ~/build/static/vsqlite---master
	cd ~/build/static && unzip vsqlite---master.zip && cd vsqlite---master && libtoolize --force && aclocal && automake --force-missing --add-missing && autoconf && sed -i 's/BOOST_/#BOOST_/g' ./configure && ./configure --enable-static --disable-shared && make || ls .libs
	cd ~/build && g++ -L./static/vsqlite---master/.libs -L/usr/lib/x86_64-linux-gnu/ main.cpp -static -lvsqlitepp -lsqlite3 -ldl -pthread -lboost_filesystem -o /tmp/test01_static
	rm -rf ~/build
	/tmp/test01_static
clean: test01
	rm -f test01
	rm -f test01_static
