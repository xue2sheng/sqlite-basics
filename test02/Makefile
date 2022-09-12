all: test02.db src/main.rs
	RUSTFLAGS='-C target-feature=+crt-static' cargo run --target=x86_64-unknown-linux-musl --release -q
static-binary:
	mkdir -p ~/build
	cp -r src ~/build/src
	cp Makefile ~/build
	cp Cargo.toml ~/build
	cp test02.db ~/build
	cd ~/build && RUSTFLAGS='-C target-feature=+crt-static' cargo run --target=x86_64-unknown-linux-musl --release -q
	cp build/target/x86_64-unknown-linux-musl/release/test02 /tmp/test02_static
	rm -rf ~/build
clean: target/
	rm -rf target/
