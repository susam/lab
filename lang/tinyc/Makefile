tinyc: FORCE
	$(CC) -g -O0 -Wall -Wextra -std=c89 -pedantic tinyc.c -o tinyc

test: tinyc
	for f in ex*.c; do \
	  echo "$$f"; cat "$$f"; ./tinyc < "$$f" > out.txt; cat out.txt; diff out.txt "$$f{%.c}.txt"; \
	done

FORCE:
