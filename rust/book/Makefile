001-hello: FORCE
	rustfmt --check $@.rs
	rustc $@.rs
	./$@

002-cargo: FORCE
	[ -d p002-cargo/ ] || cargo new p002-cargo
	cd p002-cargo/ && cargo fmt --check && cargo run

003-game: FORCE
	[ -d p003-game/ ] || cargo new p003-game
	cd p003-game/ && cargo fmt --check && cargo run

FORCE:
