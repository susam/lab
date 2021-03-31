*.cc: clean
	c++ -g -std=c++11 -Wall -Wextra -pedantic "$@" 2>&1
	sh test/test.sh "$@"
	make clean

clean:
	rm -rf *.out *.dSYM input.txt expected.txt output.txt
