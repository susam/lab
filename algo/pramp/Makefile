help:
	@echo 'Usage:'
	@echo '  make [filename]'
	@echo '  make [target]'
	@echo
	@echo 'Examples:'
	@echo '  make merging_packages.py'
	@echo '  make clean'
	@echo
	@echo 'Available targets:'
	@echo '  all    Compile and run all solutions.'
	@echo '  cc     Compile and run all C++ solutions.'
	@echo '  py     Compile and run all Python solutions.'
	@echo '  java   Compile and run all Java solutions.'
	@echo '  clean  Remove automatically generated files.'

all: py java

cc py java:
	for f in *.$@; do make "$$f" || exit 1; done

*.java: clean
	javac "$@"
	java Test
	make clean

*.py: clean
	python3 "$@"
	make clean

clean:
	rm -rf *.class

FORCE:
