all: main.go test03.db
	go build -a -ldflags '-s -w' -o test03 && ./test03
clean: test03
	rm test03
