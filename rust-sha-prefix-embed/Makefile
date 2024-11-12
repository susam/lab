run:
	cargo fmt
	cargo build --release
	time target/release/sha-prefix-embed

drun:
	cargo fmt
	cargo build
	RUST_BACKTRACE=1 target/debug/sha-prefix-embed

clean:
	rm -rf target/
