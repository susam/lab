pdf: clean
	pdflatex foo.tex
	pdflatex foo.tex
	make view FILE=foo.pdf

pandoc: pandoc-standalone pandoc-template

pandoc1:
	pandoc foo.tex --standalone --mathjax -H pandoc-standalone-head.html \
	--shift-heading-level-by=1 -o foo-pandoc1.html
	make view FILE=foo-pandoc1.html
	make blob FILE=foo-pandoc1.html

pandoc2:
	pandoc foo.tex --template=pandoc-template --mathjax \
	--shift-heading-level-by=1 -o foo-pandoc2.html
	make view FILE=foo-pandoc2.html
	make blob FILE=foo-pandoc2.html

view:
	if command -v xdg-open > /dev/null; then \
	    xdg-open "$(FILE)"; \
	elif command -v open > /dev/null; then \
	    open "$(FILE)"; \
	else \
	    echo Cannot find xdg-open or open; \
	fi

DIST = ../../../blob/lab/tex/latex-to-html/
blob:
	mkdir -p $(DIST)
	cp $(FILE) $(DIST)
	# --------------------------------------------------------------
	# File copied to:
	#
	#     $(DIST)$(FILE)
	#
	# Remember to commit it and publish.
	# --------------------------------------------------------------

clean:
	rm -rf *.aux *.log *.out
