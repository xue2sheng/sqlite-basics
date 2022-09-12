all: main.c test00.db
	gcc main.c -lsqlite3 -o test00 && ./test00
additional: main.c test00.db
	g++ -L./static -L/usr/lib main.c -static -lsqlite3 -o test00_static && ./test00_static
static-binary: main.c test00.db
	mkdir -p ~/build
	cp main.c ~/build
	cd ~/build && gcc -L/usr/lib/x86_64-linux-gnu/ main.c -static -lsqlite3 -lm -ldl -pthread -o /tmp/test00_static
	rm -rf ~/build
	/tmp/test00_static
clean: test01
	rm -f test00
	rm -f test00_static
