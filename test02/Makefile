all: test02.db src/main.rs
	RUSTFLAGS='-C target-feature=+crt-static' cargo run --target=x86_64-unknown-linux-musl --release -q
static-binary: test02.db src/main.rs
	mkdir -p ~/build
	cp -r src ~/build/src
	cp Makefile ~/build
	cp Cargo.toml ~/build
	cd ~/build && RUSTFLAGS='-C target-feature=+crt-static' cargo build --target=x86_64-unknown-linux-musl --release -q
	mv ~/build/target/x86_64-unknown-linux-musl/release/test02 /tmp/test02_static
	rm -rf ~/build
	/tmp/test02_static
clean: target/
	rm -rf target/
