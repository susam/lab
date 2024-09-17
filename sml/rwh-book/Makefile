SMLNJ = sml
MLTON = mlton

p001-hello \
p002-arithmetic \
: FORCE
	@if command -v "$(SMLNJ)" > /dev/null; then \
	echo ===== SMLNJ =====; CM_VERBOSE=false "$(SMLNJ)" < $@.sml; fi
	@if command -v "$(MLTON)" > /dev/null; then \
	echo ===== MLTON =====; "$(MLTON)" $@.sml && ./$@; fi

clean:
	ls -1 | grep -vE "Makefile|\.sml$$" | xargs rm
	rm -rf foo* bar* baz*

FORCE:
