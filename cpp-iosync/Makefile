record:
	make all > result.txt 2>&1

all: version compare

version:
	uname -a
	c++ --version

compare:
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 printf.cc && time ./a.out > num.txt
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 cout.cc && time ./a.out > num.txt
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 cout-sync.cc && time ./a.out > num.txt
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 scanf.cc && time ./a.out < num.txt
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 cin.cc && time ./a.out < num.txt
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 cin-sync.cc && time ./a.out < num.txt
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 printf-scanf.cc && time ./a.out < num.txt > out.txt
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 cin-cout.cc && time ./a.out < num.txt > out.txt
	c++ -std=c++11 -Wall -Wextra -pedantic -O2 cin-cout-sync.cc && time ./a.out < num.txt > out.txt
