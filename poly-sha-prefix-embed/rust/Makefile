run:
	cargo fmt
	cargo build --release
	time target/release/sha-prefix-embed

diff:
	diff -u ../../rust-sha-prefix-embed/sha-prefix-embed.rs sha-prefix-embed.rs
