help:
	@echo 'Usage:'
	@echo '  make [filename]'
	@echo '  make [target]'
	@echo
	@echo 'Examples:'
	@echo '  make two_sum.cc'
	@echo '  make all'
	@echo
	@echo 'Available targets:'
	@echo '  all    Compile and run all solutions.'
	@echo '  last   Compile and run last modified solution.'
	@echo '  head   Run "last" target but truncate output (useful to see first error).'
	@echo '  clean  Remove automatically generated files.'
	
last:
	make "$$(ls -t *.cc | head -n 1)"

head:
	make last 2>&1 | head -n 20
	@echo
	@echo '*** Note: Output above may be truncated! ***'

all: cc

cc:
	for f in *.$@; do make "$$f" || exit 1; done

*.cc: clean
	c++ -g -std=c++11 -pedantic -Wall -Wextra $@ 2>&1
	./a.out
	make clean

clean:
	rm -rf *.out *.out.dSYM
