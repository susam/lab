all: c cc go rust java python
	for f in *hello; do echo Executing ./$$f ...; ./$$f; done
	java Hello
	du -b *-hello Hello.class __pycache__/*.pyc
	ldd *-hello || :

c:
	cc -std=c89 -Wall -Wextra -Wpedantic hello.c -o c-hello

cc:
	c++ -std=c++11 -Wall -Wextra -Wpedantic hello.cc -o cpp-hello

go:
	go build -o go-hello hello.go

rust:
	rustc hello.rs -o rust-hello

java:
	javac Hello.java

python:
	python3 -m hello

clean:
	rm -rf *-hello Hello.class __pycache__
