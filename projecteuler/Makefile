DOC = susam-projecteuler

pdf:
	cd tex && pdflatex main && pdflatex main
	mv tex/main.pdf "tex/$(DOC).pdf"
	make view FILE=tex/$(DOC).pdf
	cp tex/$(DOC).pdf ../../blob/lab/projecteuler
	make clean

1 2:
	PN=$$(printf '%04d' "$@"); ( \
	    if [ -e tex/$$PN.tex ]; then make single PN=$$PN; fi; \
	    c++ -std=c++17 -pedantic -Wall -Wextra c++/p$$PN.cc \
	)
	# -------------------------------------------------------------
	@./a.out
	# -------------------------------------------------------------
	make clean

single:
	cd tex && pdflatex '\def\pn{$(PN)}\input{single}'
	mv tex/single.pdf tex/$(DOC)-$(PN).pdf
	make view FILE=tex/$(DOC)-$(PN).pdf
	make clean

FILE = tex/$(DOC).pdf

view:
	if command -v xdg-open > /dev/null; then \
	    xdg-open "$(FILE)"; \
	elif command -v open > /dev/null; then \
	    open "$(FILE)"; \
	else \
	    echo Cannot find xdg-open or open; \
	fi

clean:
	find . -name "*.out" -exec rm {} +
	find . -name "*.aux" -exec rm {} +
	find . -name "*.log" -exec rm {} +
	find . -name "*.toc" -exec rm {} +
