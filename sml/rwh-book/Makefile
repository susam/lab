SMLNJ = sml
MLTON = mlton

p001-hello \
p002-arithmetic \
p003-type-assertion \
p004-type-binding \
p005-value-binding \
p006-substitution-principle \
p007-let-expression \
p008-local-declaration \
p009-function \
p010-scope \
p011-tuple \
p012-tuple-pattern \
p013-record \
: FORCE
	@if command -v "$(SMLNJ)" > /dev/null; then \
	echo ===== SMLNJ =====; CM_VERBOSE=false "$(SMLNJ)" < $@.sml; fi
	@if command -v "$(MLTON)" > /dev/null; then \
	echo ===== MLTON =====; "$(MLTON)" $@.sml && ./$@ && ./$@ > out/$@.txt; fi

clean:
	ls -1 | grep -vE "Makefile|\.sml$$|out$$" | xargs rm
	rm -rf foo* bar* baz*

FORCE:
