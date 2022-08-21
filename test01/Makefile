all: main.cpp test01.db
	g++ -lvsqlitepp main.cpp -o test01 && ./test01
additional:
	g++ -L./static -L/usr/lib main.cpp -static -lvsqlitepp -lsqlite3 -lboost_filesystem -o test01_static && ./test01_static
clean: test01
	rm -f test01
	rm -f test01_static
