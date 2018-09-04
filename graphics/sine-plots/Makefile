all: output convert blob

output:
	. ./e && python3 sine.py
	. ./e && python3 xkcd-sine.py
	. ./e && pdflatex sine.tex
	. ./e && xelatex xkcd-sine.tex

convert:
	gs -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m \
	   -r300 -dGraphicsAlphaBits=4 -dTextAlphaBits=4 \
	   -sOutputFile=sine-tex.png sine.pdf
	gs -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m \
	   -r300 -dGraphicsAlphaBits=4 -dTextAlphaBits=4 \
	   -sOutputFile=xkcd-sine-tex.png xkcd-sine.pdf

DEST = ../../../blob/img/sine-plots
blob:
	mkdir -p "$(DEST)"
	cp sine-py.png "$(DEST)"
	cp xkcd-sine-py.png "$(DEST)"
	cp sine-tex.png "$(DEST)"
	cp xkcd-sine-tex.png "$(DEST)"

deps:
	# LaTeX user tree.
	echo export TEXMFHOME=texmf > e
	if [ ! -e texmf/tlpkg/texlive.tlpdb ]; then \
	. ./e && tlmgr init-usertree; fi
	. ./e && tlmgr --usermode install standalone pgfplots
	# Python virtual environment.
	python3 -m venv venv
	echo . venv/bin/activate >> e
	. ./e && pip install matplotlib

rmdeps:
	rm -rf texmf venv

clear:
	rm -f *.png *.pdf

clean:
	rm -rf *.log *.aux
