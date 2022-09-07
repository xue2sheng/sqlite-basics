all: main.go test03.db
	go build -a -ldflags '-s -w' -o test03 && ./test03
static-binary: main.go test03.db go.mod go.sum
	mkdir -p ~/build
	cp main.go ~/build/main.go 
	cp go.mod ~/build/go.mod 
	cp go.sum ~/build/go.sum	
	cd ~/build && GOOS=linux GOARCH=amd64 GO111MODULE=on go build -a -ldflags '-extldflags "-static"' -o /tmp/test03_static
	rm -rf ~/build
	/tmp/test03_static
clean:  
	rm -rf test03

