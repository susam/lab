all: output convert blob

output:
	. ./venv && python3 sine.py
	. ./venv && python3 xkcd-sine.py
	. ./texenv && pdflatex sine.tex
	. ./texenv && xelatex xkcd-sine.tex

convert:
	gs -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m \
	   -r300 -dGraphicsAlphaBits=4 -dTextAlphaBits=4 \
	   -sOutputFile=sine-tex.png sine.pdf
	gs -dSAFER -dBATCH -dNOPAUSE -sDEVICE=png16m \
	   -r300 -dGraphicsAlphaBits=4 -dTextAlphaBits=4 \
	   -sOutputFile=xkcd-sine-tex.png xkcd-sine.pdf

DEST = ../../../blob/lab/graphics/sine-plots
blob:
	mkdir -p "$(DEST)"
	cp sine-py.png "$(DEST)"
	cp xkcd-sine-py.png "$(DEST)"
	cp sine-tex.png "$(DEST)"
	cp xkcd-sine-tex.png "$(DEST)"

deps:
	# LaTeX user tree.
	echo export TEXMFHOME=texmf > texenv
	if [ ! -e texmf/tlpkg/texlive.tlpdb ]; then \
	. ./texenv && tlmgr init-usertree; fi
	. ./texenv && tlmgr --usermode install standalone pgfplots
	# Python virtual environment.
	python3 -m venv ~/.venv/sine-plots
	echo . ~/.venv/sine-plots/bin/activate >> venv
	. ./venv && pip install matplotlib

rmdeps:
	rm -rf texmf ~/.venv/sine-plots

clear:
	rm -f *.png *.pdf

clean:
	rm -rf *.log *.aux
