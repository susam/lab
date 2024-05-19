p001-hello \
p004-variables \
p005-constants \
p006-shadowing \
p007-integer \
p008-float \
p009-numeric-operations \
p010-bool \
p011-char \
p012-tuple \
: FORCE
	rustfmt --check $@.rs
	rustc $@.rs
	./$@

p002-cargo: FORCE
	[ -d p002-cargo/ ] || cargo new p002-cargo
	cd p002-cargo/ && cargo fmt --check && cargo run

p003-game: FORCE
	[ -d p003-game/ ] || cargo new p003-game
	cd p003-game/ && cargo fmt --check && cargo run

clean:
	find . -name "target" -exec rm -rf {} +

FORCE:
