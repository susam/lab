FILENAME=listings-fonts-columns-spaces

all: pdf view filebin

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

clean:
	rm -rf *.log *.aux *.pdf *.toc

filebin:
	mkdir -p ~/"git/filebin/pdf/$$(basename "$$PWD")"
	cp "$(FILENAME).pdf" ~/"git/filebin/pdf/$$(basename "$$PWD")"
