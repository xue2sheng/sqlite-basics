all: test02.db src/main.rs
	RUSTFLAGS='-C target-feature=+crt-static' cargo run --target=x86_64-unknown-linux-musl --release -q
clean: target/
	rm -rf target/
