FILENAME=lst-min-params

all: pdf view blob

pdf:
	pdflatex "$(FILENAME).tex"
	pdflatex "$(FILENAME).tex"

view:
	if command -v xdg-open > /dev/null; then \
	    xdg-open "$(FILENAME).pdf"; \
	elif command -v open > /dev/null; then \
	    open "$(FILENAME).pdf"; \
	else \
	    echo Cannot find xdg-open or open.; \
	fi

clear:
	rm -f *.pdf

clean:
	rm -f *.log *.aux *.pdf *.toc

DEST = ../../../blob/lab/tex/lst-min-params
blob:
	mkdir -p "$(DEST)"
	cp "$(FILENAME).pdf" "$(DEST)"
