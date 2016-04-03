all: main work.so

main: main.c work.h
	gcc -std=c99 -pedantic -Wall -Wextra -ldl -o main main.c

work.so: work.c work.h
	gcc -std=c99 -pedantic -Wall -Wextra -shared -fPIC -o work.so work.c

clean:
	rm main work.so
