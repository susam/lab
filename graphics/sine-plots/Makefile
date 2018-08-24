all: clear
	. ./venv && python3 sine.py
	. ./venv && python3 xkcd-sine.py
	pdflatex sine.tex
	xelatex xkcd-sine.tex

texsetup:
	tlmgr update --self
	tlmgr install pgfplots

venv: FORCE
	python3 -m venv ~/.venv/sine
	echo . ~/.venv/sine/bin/activate > venv
	. ./venv && pip install matplotlib

clear:
	rm -f *.png *.pdf

clean:
	rm -rf *.log *.aux

FORCE:
