all:
	for f in *.java; do make run FILE="$$f"; done

*.java: FORCE
	make run FILE="$@"

run: clean
	javac $(FILE)
	FILE=$(FILE); java $${FILE%.*}
	make clean

clean:
	rm -f *.class

FORCE:
